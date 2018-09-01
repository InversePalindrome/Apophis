/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"
#include "BodyComponent.hpp"
#include "BodySerializer.hpp"

#include "CCIMGUI.h"

#include <imgui.h>

#include <variant>
#include <algorithm>


BodyComponent::BodyComponent() :
	body(nullptr),
	AABB({ {FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX} }),
	shapeIndex(0)
{
}

void BodyComponent::load(const pugi::xml_node& componentNode)
{
	BodyParser::parseBody(body, componentNode);

	for (const auto fixtureNode : componentNode.children())
	{
		b2FixtureDef fixtureDef;
		BodyParser::parseFixtureDef(fixtureDef, fixtureNode);

		std::variant<b2CircleShape, b2EdgeShape, b2PolygonShape, b2ChainShape> shape;

		if (std::strcmp(fixtureNode.name(), "Circle") == 0)
		{
			b2CircleShape circle;
			BodyParser::parseCircleShape(circle, fixtureNode);
			shape = circle;
		}
		else if (std::strcmp(fixtureNode.name(), "Edge") == 0)
		{
			b2EdgeShape edge;
			BodyParser::parseEdgeShape(edge, fixtureNode);
			shape = edge;
		}
		else if (std::strcmp(fixtureNode.name(), "Polygon") == 0)
		{
			b2PolygonShape polygon;
			BodyParser::parsePolygonShape(polygon, fixtureNode);
			shape = polygon;
		}
		else if (std::strcmp(fixtureNode.name(), "Chain") == 0)
		{
			b2ChainShape chain;
			BodyParser::parseChainShape(chain, fixtureNode);
			shape = chain;
		}

		std::visit([&fixtureDef](auto& shape) { fixtureDef.shape = &shape; }, shape);

		createFixture(fixtureDef);
	}

	computeAABB();
}

void BodyComponent::save(pugi::xml_node& componentNode) const
{
	BodySerializer::saveBody(body, componentNode);

	for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		auto fixtureNode = componentNode.append_child();

		BodySerializer::saveFixture(fixture, fixtureNode);
		
		switch (fixture->GetType())
		{
		case b2Shape::e_circle:
			BodySerializer::saveCircle(static_cast<const b2CircleShape*>(fixture->GetShape()), fixtureNode);
		    break;
		case b2Shape::e_edge:
			BodySerializer::saveEdge(static_cast<const b2EdgeShape*>(fixture->GetShape()), fixtureNode);
			break;
		case b2Shape::e_polygon:
			BodySerializer::savePolygon(static_cast<const b2PolygonShape*>(fixture->GetShape()), fixtureNode);
		    break;
		case b2Shape::e_chain:
			BodySerializer::saveChain(static_cast<const b2ChainShape*>(fixture->GetShape()), fixtureNode);
			break;
		}
	}
}

void BodyComponent::display()
{
	if (ImGui::TreeNode("Body"))
	{
		ImGui::SameLine();

		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			ImGui::OpenPopup("Add Fixture");
		}

		if (auto isOpen = true; ImGui::BeginPopupModal("Add Fixture", &isOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			const char* shapes[] = { "Circle", "Edge", "Polygon", "Chain" };

			if (ImGui::Combo("Shape", &shapeIndex, shapes, 4))
			{
				verticesToAdd.clear();

				switch (static_cast<b2Shape::Type>(shapeIndex))
				{
				case b2Shape::e_circle:
				{
					b2CircleShape circle;
					circle.m_radius = 1.f;

					shapeToAdd = circle;
				}
					break;
				case b2Shape::e_edge:
				{
					b2EdgeShape edge;
					edge.m_vertex1.SetZero();
					edge.m_vertex2.SetZero();

					shapeToAdd = edge;
				}
					break;
				case b2Shape::e_polygon:
					shapeToAdd = b2PolygonShape();
					break;
				case b2Shape::e_chain:
					shapeToAdd = b2ChainShape();
					break;
				}
			}

			std::visit([this](auto& shape)
			{
				using ShapeType = std::decay_t<decltype(shape)>;

				if constexpr(std::is_same_v<ShapeType, b2CircleShape>)
				{
					ImGui::InputFloat("Radius", &shape.m_radius);
					ImGui::InputFloat2("Center", &shape.m_p.x);
				}
				else if constexpr(std::is_same_v<ShapeType, b2EdgeShape>)
				{
					ImGui::Checkbox("Has Vertex 0", &shape.m_hasVertex0);
					ImGui::SameLine();
					ImGui::Checkbox("Has Vertex 3", &shape.m_hasVertex3);

					if (shape.m_hasVertex0)
					{
						ImGui::InputFloat2("Vertex 0", &shape.m_vertex0.x);
					}

					ImGui::InputFloat2("Vertex 1", &shape.m_vertex1.x);
					ImGui::InputFloat2("Vertex 2", &shape.m_vertex2.x);

					if (shape.m_hasVertex3)
					{
						ImGui::InputFloat2("Vertex 3", &shape.m_vertex3.x);
					}
				
				}
				else if constexpr(std::is_same_v<ShapeType, b2PolygonShape>)
				{
					ImGui::Text("Vertices");
					ImGui::SameLine();

					if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
					{
						verticesToAdd.push_back({ 0.f, 0.f });
					}

					int i = 0;

					for (auto vertexItr = std::begin(verticesToAdd); vertexItr != std::end(verticesToAdd);)
					{
						ImGui::PushID(i++);

						ImGui::InputFloat2(("Vertex " + std::to_string(i)).c_str(), &vertexItr->x);
						ImGui::SameLine();
						if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
						{
							vertexItr = verticesToAdd.erase(vertexItr);
						}
						else
						{
							++vertexItr;
						}

						ImGui::PopID();
					}
				}
				else if constexpr(std::is_same_v<ShapeType, b2ChainShape>)
				{
					ImGui::Text("Vertices");
					ImGui::SameLine();

					if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
					{
						verticesToAdd.push_back({ 0.f, 0.f });
					}

					int i = 0;

					for (auto vertexItr = std::begin(verticesToAdd); vertexItr != std::end(verticesToAdd);)
					{
						ImGui::PushID(i++);

						ImGui::InputFloat2(("Vertex " + std::to_string(i)).c_str(), &vertexItr->x);
						ImGui::SameLine();
						if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
						{
							vertexItr = verticesToAdd.erase(vertexItr);
						}
						else
						{
							++vertexItr;
						}

						ImGui::PopID();
					}
				}
			}, shapeToAdd);

			if (ImGui::Button("Add"))
			{
				b2FixtureDef fixtureDef;
				
				std::visit([this, &fixtureDef](auto& shape)
				{
					using ShapeType = std::decay_t<decltype(shape)>;

					if constexpr(std::is_same_v<ShapeType, b2PolygonShape>)
					{
						shape.Set(verticesToAdd.data(), verticesToAdd.size());
					}
					else if constexpr(std::is_same_v<ShapeType, b2ChainShape>)
					{
						shape.CreateChain(verticesToAdd.data(), verticesToAdd.size());
					}

					fixtureDef.shape = &shape; 
				}, shapeToAdd);

				createFixture(fixtureDef);
				
				verticesToAdd.clear();

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		const char* bodyTypes[] = { "Static", "Kinematic", "Dynamic" };

		if (auto bodyType = static_cast<int>(getBodyType()); ImGui::Combo("Type", &bodyType, bodyTypes, 3))
		{
			setBodyType(static_cast<b2BodyType>(bodyType));
		}

		if (auto position = getPosition(); ImGui::InputFloat2("Position(X, Y)", &position.x))
		{
			setPosition(position);
		}
		if (auto angle = getAngle(); ImGui::InputFloat("Angle", &angle))
		{
			setAngle(angle);
		}
		if (auto linearDamping = getLinearDamping(); ImGui::InputFloat("Linear Damping", &linearDamping))
		{
			setLinearDamping(linearDamping);
		}
		if (auto angularDamping = getAngularDamping(); ImGui::InputFloat("Angular Damping", &angularDamping))
		{
			setAngularDamping(angularDamping);
		}
		if (auto rotationFixed = isRotationFixed(); ImGui::Checkbox("Rotation Fixed", &rotationFixed))
		{
			setRotationFixed(rotationFixed);
		}
		if (auto bullet = isBullet(); ImGui::Checkbox("Bullet", &bullet))
		{
			setBullet(bullet);
		}

		int fixtureID = 0;
		std::vector<b2Fixture*> fixturesToDestroy;

		for (auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			auto isFixtureOpen = ImGui::TreeNode(("Fixture " + std::to_string(fixtureID++)).c_str());

			ImGui::SameLine();

			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				fixturesToDestroy.push_back(fixture);
			}

			if (isFixtureOpen)
			{
				if (auto density = fixture->GetDensity(); ImGui::InputFloat("Density", &density))
				{
					fixture->SetDensity(density);
				}
				if (auto friction = fixture->GetFriction(); ImGui::InputFloat("Friction", &friction))
				{
					fixture->SetFriction(friction);
				}
				if (auto restitution = fixture->GetRestitution(); ImGui::InputFloat("Restitution", &restitution))
				{
					fixture->SetRestitution(restitution);
				}
				if (auto sensor = fixture->IsSensor(); ImGui::Checkbox("Sensor", &sensor))
				{
					fixture->SetSensor(sensor);
				}
		
				switch (fixture->GetShape()->GetType())
				{
				case b2Shape::e_circle:
					if (ImGui::TreeNode("Circle"))
					{
						const auto* circle = static_cast<const b2CircleShape*>(fixture->GetShape());

						ImGui::Text("Radius: %.2f", circle->m_radius);
						ImGui::Text("Center(X, Y): (%.2f, %.2f)", circle->m_p.x, circle->m_p.y);

						ImGui::TreePop();
					}
					break;
				case b2Shape::e_edge:
					if (ImGui::TreeNode("Edge"))
					{
						const auto* edge = static_cast<const b2EdgeShape*>(fixture->GetShape());

						if (edge->m_hasVertex0)
						{
							ImGui::Text("Vertex 0(X, Y): (%.2f, %.2f)", edge->m_vertex0.x, edge->m_vertex0.y);
						}

						ImGui::Text("Vertex 1(X, Y): (%.2f, %.2f)", edge->m_vertex1.x, edge->m_vertex1.y);
						ImGui::Text("Vertex 2(X, Y): (%.2f, %.2f)", edge->m_vertex2.x, edge->m_vertex2.y);

						if (edge->m_hasVertex3)
						{
							ImGui::Text("Vertex 3(X, Y): (%.2f, %.2f)", edge->m_vertex3.x, edge->m_vertex3.y);
						}

						ImGui::TreePop();
					}
					break;
				case b2Shape::e_polygon:
					if (ImGui::TreeNode("Polygon"))
					{
						const auto* polygon = static_cast<const b2PolygonShape*>(fixture->GetShape());
					   
						for (int i = 0; i < polygon->m_count; ++i)
						{
							ImGui::Text("Vertex %d (X, Y): (%.2f, %.2f)", i, polygon->m_vertices[i].x, polygon->m_vertices[i].y);
						}

						ImGui::TreePop();
					}
					break;
				case b2Shape::e_chain:
					if (ImGui::TreeNode("Chain"))
					{
						const auto* chain = static_cast<const b2ChainShape*>(fixture->GetShape());
						
						for (int i = 0; i < chain->m_count; ++i)
						{
							ImGui::Text("Vertex %d (X, Y): (%.2f, %.2f)", i, chain->m_vertices[i].x, chain->m_vertices[i].y);
						}

						ImGui::TreePop();
					}
					break;
				}

				ImGui::TreePop();
			}
		}

		for (const auto& fixture : fixturesToDestroy)
		{
			destroyFixture(fixture);
		}

		ImGui::TreePop();
	}
}

b2Body* BodyComponent::getBody()
{
	return body;
}

void BodyComponent::setBody(b2Body* body)
{
	this->body = body;
	body->SetUserData(&userData);
}

b2Fixture* BodyComponent::getFixtureList()
{
	return body->GetFixtureList();
}

const b2Fixture* BodyComponent::getFixtureList() const
{
	return body->GetFixtureList();
}

b2JointEdge* BodyComponent::getJointList()
{
	return body->GetJointList();
}

const b2JointEdge* BodyComponent::getJointList() const
{
	return body->GetJointList();
}

std::any BodyComponent::getUserData() const
{
	return userData;
}

void BodyComponent::setUserData(const std::any& userData)
{
	this->userData = userData;
}

b2BodyType BodyComponent::getBodyType() const
{
	return body->GetType();
}

void BodyComponent::setBodyType(b2BodyType bodyType)
{
	body->SetType(bodyType);
}

b2Vec2 BodyComponent::getPosition() const
{
	return body->GetPosition();
}

void BodyComponent::setPosition(const b2Vec2& position)
{
    body->SetTransform(position, body->GetAngle());
}

b2Vec2 BodyComponent::getLinearVelocity() const
{
	return body->GetLinearVelocity();
}

void BodyComponent::setLinearVelocity(const b2Vec2& linearVelocity)
{
    body->SetLinearVelocity(linearVelocity);
}

float BodyComponent::getAngularVelocity() const
{
	return body->GetAngularVelocity();
}

void BodyComponent::setAngularVelocity(float angularVelocity)
{
    body->SetAngularVelocity(angularVelocity);
}

float BodyComponent::getAngle() const
{
	return body->GetAngle();
}

void BodyComponent::setAngle(float angle)
{
    body->SetTransform(body->GetPosition(), angle);
}

float BodyComponent::getMass() const
{
	return body->GetMass();
}

float BodyComponent::getInertia() const
{
	return body->GetInertia();
}

float BodyComponent::getLinearDamping() const
{
	return body->GetLinearDamping();
}

void BodyComponent::setLinearDamping(float linearDamping)
{
	body->SetLinearDamping(linearDamping);
}

float BodyComponent::getAngularDamping() const
{
	return body->GetAngularDamping();
}

void BodyComponent::setAngularDamping(float angularDamping)
{
	body->SetAngularDamping(angularDamping);
}

b2AABB BodyComponent::getAABB() const
{
	return AABB;
}

void BodyComponent::computeAABB()
{
	for (const auto* fixture = getFixtureList(); fixture; fixture = fixture->GetNext())
	{
		for (int child = 0; child < fixture->GetShape()->GetChildCount(); ++child)
		{
			b2Transform transform;
			transform.SetIdentity();

			b2AABB shapeAABB{ { FLT_MAX, FLT_MAX },{ -FLT_MAX, -FLT_MAX } };
			fixture->GetShape()->ComputeAABB(&shapeAABB, transform, child);

			AABB.Combine(shapeAABB);
		}
	}
}

b2Fixture* BodyComponent::createFixture(const b2FixtureDef& fixtureDef)
{
	return body->CreateFixture(&fixtureDef);
}

void BodyComponent::destroyFixture(b2Fixture* fixture)
{
	body->DestroyFixture(fixture);
}

void BodyComponent::applyLinearImpulse(const b2Vec2& linearImpulse)
{
    body->ApplyLinearImpulse(linearImpulse, body->GetWorldCenter(), true);
}

void BodyComponent::applyAngularImpulse(float angularImpulse)
{
	body->ApplyAngularImpulse(angularImpulse, true);
}

void BodyComponent::applyLinearForce(const b2Vec2& linearForce)
{
    body->ApplyForceToCenter(linearForce, true);
}

void BodyComponent::applyAngularForce(float angularForce)
{
    body->ApplyTorque(angularForce, true); 
}

bool BodyComponent::isRotationFixed() const
{
	return body->IsFixedRotation();
}

void BodyComponent::setRotationFixed(bool rotationFixed)
{
	body->SetFixedRotation(rotationFixed);
}

bool BodyComponent::isBullet() const
{
	return body->IsBullet();
}

void BodyComponent::setBullet(bool bullet)
{
	body->SetBullet(bullet);
}

bool BodyComponent::contains(const b2Vec2& point) const
{
	for (const auto* fixture = getFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if (fixture->TestPoint(point))
		{
			return true;
		}
	}
	
	return false;
}

bool BodyComponent::raycast(b2RayCastOutput& output, const b2RayCastInput& input) const
{
	for (const auto* fixture = getFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if (fixture->RayCast(&output, input, 0))
		{
			return true;
		}
	}

	return false;
}