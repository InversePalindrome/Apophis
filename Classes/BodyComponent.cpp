/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <boost/range/combine.hpp>


BodyComponent::BodyComponent(const pugi::xml_node& componentNode) :
	body(nullptr)
{
	initBodyDef(componentNode);
	
	for (const auto fixtureNode : componentNode.children())
	{
		initFixtureDef(fixtureNode);
	}
}

void BodyComponent::createBody(b2World& world)
{
	body = world.CreateBody(&bodyDef);
	body->SetUserData(&userData);

	for (const auto& fixtureDef : fixtureDefs)
	{
		body->CreateFixture(&fixtureDef);
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

std::any BodyComponent::getUserData() const
{
	return userData;
}

void BodyComponent::setUserData(std::any userData)
{
	this->userData = userData;
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

		shapes.push_back(circle);
	}
	else if (std::strcmp(fixtureNode.name(), "Rectangle") == 0)
	{
		b2PolygonShape rectangle;
		b2Vec2 center(0.f, 0.f);
		float width = 0.f, height = 0.f, angle = 0.f;

		if (const auto xAttribute = fixtureNode.attribute("x"))
		{
			center.x = xAttribute.as_float();
		}
		if (const auto yAttribute = fixtureNode.attribute("y"))
		{
			center.y = yAttribute.as_float();
		}
		if (const auto widthAttribute = fixtureNode.attribute("width"))
		{
			width = widthAttribute.as_float();
		}
		if (const auto heightAttribute = fixtureNode.attribute("height"))
		{
			height = heightAttribute.as_float();
		}
		if (const auto angleAttribute = fixtureNode.attribute("angle"))
		{
			angle = angleAttribute.as_float();
		}

		rectangle.SetAsBox(width, height, center, angle);

		shapes.push_back(rectangle);
	}
	else if (std::strcmp(fixtureNode.name(), "Polygon"))
	{
		b2PolygonShape polygon;

		std::vector<b2Vec2> points;

		for (const auto pointNode : fixtureNode.children("Point"))
		{
			b2Vec2 point(0.f, 0.f);

			if (const auto xAttribute = pointNode.attribute("x"))
			{
				point.x = xAttribute.as_float();
			}
			if (const auto yAttribute = pointNode.attribute("y"))
			{
				point.y = yAttribute.as_float();
			}

			points.push_back(point);
		}

		polygon.Set(points.data(), points.size());

		shapes.push_back(polygon);
	}
	
	std::visit([&fixtureDef](auto& shape) { fixtureDef.shape = &shape; }, shapes.back());

	fixtureDefs.push_back(fixtureDef);
}