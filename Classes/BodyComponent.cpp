/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <sstream>
#include <variant>


BodyComponent::BodyComponent(const tinyxml2::XMLElement* componentNode, b2World& world)
{
	createBody(componentNode, world);

	for (const auto* fixtureNode = componentNode->FirstChildElement("Fixture"); fixtureNode; fixtureNode = fixtureNode->NextSiblingElement("Fixture"))
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

b2AABB BodyComponent::getAABB() const
{
	b2AABB aabb{ {0.f, 0.f}, {0.f, 0.f} };

	b2Transform transform;
	transform.SetIdentity();

	for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		const auto* shape = fixture->GetShape();

		for (int child = 0; child < shape->GetChildCount(); ++child)
		{
			b2AABB shapeAABB;
			shape->ComputeAABB(&shapeAABB, transform, child);
			shapeAABB.lowerBound = shapeAABB.lowerBound;
			shapeAABB.upperBound = shapeAABB.upperBound;

			aabb.Combine(shapeAABB);
		}
	}

	return aabb;
}

b2Vec2 BodyComponent::getLinearVelocity() const
{
	return body->GetLinearVelocity();
}

void BodyComponent::setLinearVelocity(const b2Vec2& velocity)
{
	body->SetLinearVelocity(velocity);
}

float BodyComponent::getAngularVelocity() const
{
	return body->GetAngularVelocity();
}

void BodyComponent::setAngularVelocity(float velocity)
{
	body->SetAngularVelocity(velocity);
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

void BodyComponent::applyForce(const b2Vec2& force)
{
	body->ApplyForceToCenter(force, true);
}

void BodyComponent::applyLinearImpulse(const b2Vec2& impulse)
{
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

void BodyComponent::applyAngularImpulse(float impulse)
{
	body->ApplyAngularImpulse(impulse, true);
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

void BodyComponent::createBody(const tinyxml2::XMLElement* bodyNode, b2World& world)
{
	b2BodyDef bodyDef;

	if (const auto* bodyType = bodyNode->Attribute("type"))
	{
		bodyDef.type = static_cast<b2BodyType>(std::stoi(bodyType));
	}
	if (const auto* linearDamping = bodyNode->Attribute("linearDamping"))
	{
		bodyDef.linearDamping = std::stof(linearDamping);
	}
	if (const auto* angularDamping = bodyNode->Attribute("angularDamping"))
	{
		bodyDef.angularDamping = std::stof(angularDamping);
	}
	if (const auto* fixedRotation = bodyNode->Attribute("fixedRotation"))
	{
		std::istringstream iStream(fixedRotation);

		iStream >> std::boolalpha >> bodyDef.fixedRotation;
	}
	if (const auto* bullet = bodyNode->Attribute("bullet"))
	{
		std::istringstream iStream(bullet);

		iStream >> std::boolalpha >> bodyDef.bullet;
	}

	const auto* xPosition = bodyNode->Attribute("x");
	const auto* yPosition = bodyNode->Attribute("y");

	if (xPosition && yPosition)
	{
		bodyDef.position = { std::stof(xPosition), std::stof(yPosition) };
	}

	body = world.CreateBody(&bodyDef);
}

void BodyComponent::createFixture(const tinyxml2::XMLElement* fixtureNode)
{
	b2FixtureDef fixtureDef;

	std::variant<b2CircleShape, b2PolygonShape> fixtureShape;

	if (const auto* shape = fixtureNode->Attribute("shape"))
	{
		if (std::strcmp(shape, "circle") == 0)
		{
			b2CircleShape circleShape;

			const auto* xPosition = fixtureNode->Attribute("x");
			const auto* yPosition = fixtureNode->Attribute("y");

			if (xPosition && yPosition)
			{
				circleShape.m_p = { std::stof(xPosition), std::stof(yPosition) };
			}
			if (const auto* radius = fixtureNode->Attribute("radius"))
			{
				circleShape.m_radius = std::stof(radius);
			}

			fixtureShape = circleShape;

			fixtureDef.shape = &std::get<0>(fixtureShape);
		}
		else if (std::strcmp(shape, "polygon") == 0)
		{
			b2PolygonShape polyShape;

			const auto* xPosition = fixtureNode->Attribute("x");
			const auto* yPosition = fixtureNode->Attribute("y");

			if (xPosition && yPosition)
			{
				polyShape.m_centroid = { std::stof(xPosition), std::stof(yPosition) };
			}

			const auto* width = fixtureNode->Attribute("width");
			const auto* height = fixtureNode->Attribute("height");

			if (width && height)
			{
				polyShape.SetAsBox(std::stof(width), std::stof(height));
			}

			fixtureShape = polyShape;
			fixtureDef.shape = &std::get<1>(fixtureShape);
		}
	}
	if (const auto* density = fixtureNode->Attribute("density"))
	{
		fixtureDef.density = std::stof(density);
	}
	if (const auto* restitution = fixtureNode->Attribute("restitution"))
	{
		fixtureDef.restitution = std::stof(restitution);
	}
	if (const auto* sensor = fixtureNode->Attribute("sensor"))
	{
		std::istringstream iStream(sensor);

		iStream >> std::boolalpha >> fixtureDef.isSensor;
	}

	body->CreateFixture(&fixtureDef);
}