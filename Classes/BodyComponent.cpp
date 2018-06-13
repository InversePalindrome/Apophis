/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <vector>
#include <variant>


BodyComponent::BodyComponent(b2World& world, const pugi::xml_node& componentNode, void* bodyData) 
{
	createBody(world, componentNode, bodyData);

	for (const auto fixtureNode : componentNode.children())
	{
		createFixture(fixtureNode);
	}
}

b2Body* BodyComponent::getBody()
{
	return body;
}

b2Body* BodyComponent::getBody() const
{
	return body;
}

b2World* BodyComponent::getWorld()
{
	return body->GetWorld();
}

b2World* BodyComponent::getWorld() const
{
	return body->GetWorld();
}

void* BodyComponent::getUserData() const
{
	return body->GetUserData();
}

void BodyComponent::setUserData(void* userData)
{
	body->SetUserData(userData);
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

bool BodyComponent::contains(const b2Vec2& point) const
{
	for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
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
	for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if (fixture->RayCast(&output, input, 0))
		{
			return true;
		}
	}

	return false;
}

void BodyComponent::createBody(b2World& world, const pugi::xml_node& bodyNode, void* bodyData)
{
	b2BodyDef bodyDef;

	if (const auto bodyTypeAttribute = bodyNode.attribute("type"))
	{
		bodyDef.type = static_cast<b2BodyType>(bodyTypeAttribute.as_int());
	}
	if (const auto linearDampingAttribute = bodyNode.attribute("linearDamping"))
	{
		bodyDef.linearDamping = linearDampingAttribute.as_float();
	}
	if (const auto angularDampingAttribute = bodyNode.attribute("angularDamping"))
	{
		bodyDef.angularDamping = angularDampingAttribute.as_float();
	}
	if (const auto fixedRotationAttribute = bodyNode.attribute("fixedRotation"))
	{ 
		bodyDef.fixedRotation = fixedRotationAttribute.as_bool();
	}
	if (const auto bulletAttribute = bodyNode.attribute("bullet"))
	{
		bodyDef.bullet = bulletAttribute.as_bool();
	}

	bodyDef.userData = bodyData;

	body = world.CreateBody(&bodyDef);
}

void BodyComponent::createFixture(const pugi::xml_node& fixtureNode)
{
	b2FixtureDef fixtureDef;

	if (const auto densityAttribute = fixtureNode.attribute("density"))
	{
		fixtureDef.density = densityAttribute.as_float();
	}
	if (const auto frictionAttribute = fixtureNode.attribute("friction"))
	{
		fixtureDef.friction = frictionAttribute.as_float();
	}
	if (const auto restitutionAttribute = fixtureNode.attribute("restitution"))
	{
		fixtureDef.restitution = restitutionAttribute.as_float();
	}
	if (const auto sensorAttribute = fixtureNode.attribute("sensor"))
	{
		fixtureDef.isSensor = sensorAttribute.as_bool();
	}

	std::variant<b2CircleShape, b2PolygonShape> shape;

	if (std::strcmp(fixtureNode.name(), "Circle") == 0)
	{
		b2CircleShape circle;

		if (const auto xAttribute = fixtureNode.attribute("x"))
		{
			circle.m_p.x = xAttribute.as_float();
		}
		if (const auto yAttribute = fixtureNode.attribute("y"))
		{
			circle.m_p.y = yAttribute.as_float();
		}
		if (const auto radiusAttribute = fixtureNode.attribute("radius"))
		{
			circle.m_radius = radiusAttribute.as_float();
		}

		shape = circle;

		fixtureDef.shape = &std::get<0>(shape);
	}
	else if (std::strcmp(fixtureNode.name(), "Polygon") == 0)
	{
		b2PolygonShape polygon;

		std::vector<b2Vec2> vertices;

		for (const auto vertexNode : fixtureNode.children("Vertex"))
		{
			auto xAttribute = vertexNode.attribute("x");
			auto yAttribute = vertexNode.attribute("y");

			if (xAttribute && yAttribute)
			{
				vertices.push_back({ xAttribute.as_float(), yAttribute.as_float() });
			}
		}

		polygon.Set(vertices.data(), vertices.size());

		shape = polygon;
		
		fixtureDef.shape = &std::get<1>(shape);
	}

	body->CreateFixture(&fixtureDef);
}