/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <Box2D/Dynamics/b2Fixture.h>


BodyComponent::BodyComponent(b2Body* body) :
	body(body)
{
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