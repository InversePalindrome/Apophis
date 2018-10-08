/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"
#include "BodyDisplay.hpp"
#include "BodyComponent.hpp"
#include "BodySerializer.hpp"

#include "CCIMGUI.h"

#include <imgui.h>

#include <algorithm>


BodyComponent::BodyComponent() :
	body(nullptr),
	AABB({ {FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX} }),
	shapeIndex(0),
	polygonModeIndex(0),
	chainModeIndex(0),
	box(0.f, 0.f)
{
}

void BodyComponent::load(const pugi::xml_node& componentNode)
{
	BodyParser::parseBody(body, componentNode);

	for (const auto fixtureNode : componentNode.children())
	{
		b2FixtureDef fixtureDef;

		BodyParser::parseFixtureDef(fixtureDef, fixtureNode);

		if (std::strcmp(fixtureNode.name(), "Circle") == 0)
		{
			b2CircleShape circle;

			BodyParser::parseCircle(circle, fixtureNode);

			fixtureDef.shape = &circle;

			createFixture(fixtureDef);
		}
		else if (std::strcmp(fixtureNode.name(), "Edge") == 0)
		{
			b2EdgeShape edge;

			BodyParser::parseEdge(edge, fixtureNode);

			fixtureDef.shape = &edge;

			createFixture(fixtureDef);
		}
		else if (std::strcmp(fixtureNode.name(), "Polygon") == 0)
		{
			b2PolygonShape polygon;

			BodyParser::parsePolygon(polygon, fixtureNode);

			fixtureDef.shape = &polygon;

			createFixture(fixtureDef);
		}
		else if (std::strcmp(fixtureNode.name(), "Chain") == 0)
		{
			b2ChainShape chain;

			BodyParser::parseChain(chain, fixtureNode);

			fixtureDef.shape = &chain;

			createFixture(fixtureDef);
		}
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
				switch (static_cast<b2Shape::Type>(shapeIndex))
				{
				case b2Shape::e_circle:
				{
					b2CircleShape circle;
					circle.m_radius = 1.f;

					shape = circle;
				}
					break;
				case b2Shape::e_edge:
				{
					b2EdgeShape edge;
					edge.m_vertex1.SetZero();
					edge.m_vertex2.SetZero();

					shape = edge;
				}
					break;
				case b2Shape::e_polygon:
					shape = b2PolygonShape();
					break;
				case b2Shape::e_chain:
					shape = b2ChainShape();
					break;
				}
			}

			std::visit([this](auto& shape)
			{
				using ShapeType = std::decay_t<decltype(shape)>;

				if constexpr(std::is_same_v<ShapeType, b2CircleShape>)
				{
					BodyDisplay::displayCircle(shape);
				}
				else if constexpr(std::is_same_v<ShapeType, b2EdgeShape>)
				{
					BodyDisplay::displayEdge(shape);
				}
				else if constexpr(std::is_same_v<ShapeType, b2PolygonShape>)
				{
					BodyDisplay::displayPolygon(shape, polygonModeIndex, vertices, box);
				}
				else if constexpr(std::is_same_v<ShapeType, b2ChainShape>)
				{
					BodyDisplay::displayChain(shape, chainModeIndex, vertices);
				}
			}, shape);

			if (ImGui::Button("Add"))
			{
				b2FixtureDef fixtureDef;
				
				std::visit([this, &fixtureDef](auto& shape)
				{ 
					using ShapeType = std::decay_t<decltype(shape)>;

					if constexpr(std::is_same_v<ShapeType, b2PolygonShape>)
					{
						if (polygonModeIndex == 0)
						{
							shape.Set(vertices.data(), vertices.size());
						}
						else if (polygonModeIndex == 1)
						{
							shape.SetAsBox(box.x, box.y);
						}
					}
					else if constexpr(std::is_same_v<ShapeType, b2ChainShape>)
					{
						if (chainModeIndex == 0)
						{
							shape.CreateChain(vertices.data(), vertices.size());
						}
						else if (chainModeIndex == 1)
						{
							shape.CreateLoop(vertices.data(), vertices.size());
						}
					}

					fixtureDef.shape = &shape; 
				}, shape);

				createFixture(fixtureDef);

				vertices.clear();

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		BodyDisplay::displayBody(body);

		int fixtureID = 0;
		std::vector<b2Fixture*> fixturesToDestroy;

		for (auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			ImGui::PushID(fixtureID++);

			auto isFixtureOpen = ImGui::TreeNode("", "Fixture %d", fixtureID);
			
			ImGui::SameLine();

			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				fixturesToDestroy.push_back(fixture);
			}

			if (isFixtureOpen)
			{
				BodyDisplay::displayFixture(fixture);
		
				switch (fixture->GetShape()->GetType())
				{
				case b2Shape::e_circle:
					BodyDisplay::displayCircle(static_cast<const b2CircleShape*>(fixture->GetShape()));
					break;
				case b2Shape::e_edge:
					BodyDisplay::displayEdge(static_cast<const b2EdgeShape*>(fixture->GetShape()));
					break;
				case b2Shape::e_polygon:
					BodyDisplay::displayPolygon(static_cast<const b2PolygonShape*>(fixture->GetShape()));
					break;
				case b2Shape::e_chain:
					BodyDisplay::displayChain(static_cast<const b2ChainShape*>(fixture->GetShape()));
					break;
				}

				ImGui::TreePop();
			}

			ImGui::PopID();
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

void* BodyComponent::getUserData() const
{
	return body->GetUserData();
}

void BodyComponent::setUserData(void* userData)
{
	body->SetUserData(userData);
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