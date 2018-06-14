/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <boost/range/combine.hpp>

#include <vector>
#include <variant>


BodyComponent::BodyComponent(const pugi::xml_node& componentNode) :
	body(nullptr)
{
	initBodyDef(componentNode);
	
	for (const auto fixtureNode : componentNode.children("Fixture"))
	{
		initFixtureDef(fixtureNode);
	}
}

void BodyComponent::createBody(b2World& world)
{
	body = world.CreateBody(&bodyDef);
}

void BodyComponent::createFixtures(const std::vector<std::variant<b2CircleShape, b2PolygonShape>>& shapes)
{
	for (const auto& fixtureAndShape : boost::combine(fixtureDefs, shapes))
	{
		std::visit([fixtureAndShape](const auto& shape) { boost::get<0>(fixtureAndShape).shape = &shape; }, boost::get<1>(fixtureAndShape));

		body->CreateFixture(&boost::get<0>(fixtureAndShape));
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

void BodyComponent::initBodyDef(const pugi::xml_node& bodyNode)
{
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
}

void BodyComponent::initFixtureDef(const pugi::xml_node& fixtureNode)
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

	fixtureDefs.push_back(fixtureDef);
}