/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <algorithm>


BodyComponent::BodyComponent(b2Body* body) :
	body(body),
    AABB({ {FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX} })
{
	body->SetUserData(&userData);
}

void BodyComponent::createFixture(const b2FixtureDef& fixtureDef)
{
	fixtures.push_back(body->CreateFixture(&fixtureDef));
}

void BodyComponent::destroyFixture(b2Fixture* fixture)
{
	fixtures.erase(std::remove(std::begin(fixtures), std::end(fixtures), fixture), std::end(fixtures));

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

b2AABB BodyComponent::getAABB() const
{
	return AABB;
}

void BodyComponent::computeAABB()
{
	for (const auto& fixture : fixtures)
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

bool BodyComponent::contains(const b2Vec2& point) const
{
	for (const auto& fixture : fixtures)
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
	for (const auto& fixture : fixtures)
	{
		if (fixture->RayCast(&output, input, 0))
		{
			return true;
		}
	}

	return false;
}