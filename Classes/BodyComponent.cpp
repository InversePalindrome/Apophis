/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"
#include "BodySerializer.hpp"

#include "CCIMGUI.h"

#include <imgui.h>

#include <algorithm>


BodyComponent::BodyComponent(b2Body* body) :
	body(body),
	AABB({ {FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX} }),
	fixtureShapeToAdd(0)
{
	body->SetUserData(&userData);
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

			if (ImGui::Combo("Shape", &fixtureShapeToAdd, shapes, 4))
			{
				switch (static_cast<b2Shape::Type>(fixtureShapeToAdd))
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
				{
					b2PolygonShape polygon;

					for (int i = 0; i < b2_maxPolygonVertices; ++i)
					{
						polygon.m_vertices[i].SetZero();
					}

					shapeToAdd = polygon;
				}
					break;
				case b2Shape::e_chain:
					b2ChainShape chain;

					shapeToAdd = chain;
					break;
				}
			}

			ImGui::Text("Shape Data");

			std::visit([](auto& shape)
			{
				using ShapeType = std::decay_t<decltype(shape)>;

				if constexpr(std::is_same_v<ShapeType, b2CircleShape>)
				{
					ImGui::InputFloat2("Origin", &shape.m_p.x);
					ImGui::InputFloat("Radius", &shape.m_radius);
				}
				else if constexpr(std::is_same_v<ShapeType, b2EdgeShape>)
				{
					ImGui::Checkbox("Has Vertex 0", &shape.m_hasVertex0);
					ImGui::SameLine();
					ImGui::Checkbox("Has Vertex 3", &shape.m_hasVertex3);

					if (shape.m_hasVertex0)
					{
						ImGui::InputFloat2("Vertex 0(X, Y)", &shape.m_vertex0.x);
					}

					ImGui::InputFloat2("Vertex 1(X, Y)", &shape.m_vertex1.x);
					ImGui::InputFloat2("Vertex 2(X, Y)", &shape.m_vertex2.x);

					if (shape.m_hasVertex3)
					{
						ImGui::InputFloat2("Vertex 3(X, Y)", &shape.m_vertex3.x);
					}
				}
				else if constexpr(std::is_same_v<ShapeType, b2PolygonShape>)
				{
					ImGui::SameLine();
					if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
					{
						++shape.m_count;
					}

					for (int i = 0; i < shape.GetVertexCount(); ++i)
					{
						ImGui::PushID(i);

						ImGui::InputFloat2(("Point " + std::to_string(i)).c_str(), &shape.m_vertices[i].x);

						ImGui::PopID();
					}
				}
				else if constexpr(std::is_same_v<ShapeType, b2ChainShape>)
				{
					for (int i = 0; i < shape.m_count; ++i)
					{
						ImGui::PushID(i);

						ImGui::InputFloat2(("Point " + std::to_string(i)).c_str(), &shape.m_vertices[i].x);

						ImGui::PopID();
					}
				}
			}, shapeToAdd);

			if (ImGui::Button("Add"))
			{
				b2FixtureDef fixtureToAdd;

				std::visit([&fixtureToAdd](auto& shape)
				{
					fixtureToAdd.shape = &shape;
				}, shapeToAdd);

				createFixture(fixtureToAdd);

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
		
				ImGui::TreePop();

				switch (fixture->GetShape()->m_type)
				{
				case b2Shape::e_circle:
					if (ImGui::TreeNode("Circle"))
					{
						ImGui::TreePop();
					}
					break;
				case b2Shape::e_edge:
					if (ImGui::TreeNode("Edge"))
					{

					}
					break;
				case b2Shape::e_polygon :
					if (ImGui::TreeNode("Polygon"))
					{

					}
					break;
				case b2Shape::e_chain :
					if (ImGui::TreeNode("Chain"))
					{

					}
					break;
				}
			}
		}

		for (auto* fixture : fixturesToDestroy)
		{
			destroyFixture(fixture);
		}

		fixturesToDestroy.clear();

		ImGui::TreePop();
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

b2Body* BodyComponent::getBody()
{
	return body;
}

b2Body* BodyComponent::getBody() const
{
	return body;
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