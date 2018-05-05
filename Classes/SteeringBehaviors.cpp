/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringBehaviors.cpp
InversePalindrome.com
*/


#include "BodyData.hpp"
#include "PhysicsUtility.hpp"
#include "SteeringBehaviors.hpp"

#include <cocos/base/ccRandom.h>


void SteeringBehaviors::seek(b2Body* body, const b2Vec2& targetPosition, float maxSpeed)
{
	body->ApplyLinearImpulse(desiredVelocity(body->GetPosition(), targetPosition, maxSpeed) - body->GetLinearVelocity(), body->GetWorldCenter(), true);
}

void SteeringBehaviors::pursue(b2Body* body, const b2Vec2& targetPosition, const b2Vec2& targetVelocity, float maxSpeed, float predictionTime)
{
	auto distance = (targetPosition - body->GetPosition()).Length();

	if (body->GetLinearVelocity().Length() > distance / predictionTime)
	{
		predictionTime = distance / body->GetLinearVelocity().Length();
	}

	const auto& futurePosition = targetPosition + predictionTime * targetVelocity;

	seek(body, futurePosition, maxSpeed);
}

void SteeringBehaviors::arrive(b2Body* body, const b2Vec2& targetPosition,  float maxSpeed, float slowRadius)
{
	auto radius = (targetPosition - body->GetPosition()).Length();
	
	if (radius < slowRadius)
	{
		seek(body, targetPosition, maxSpeed * radius / slowRadius);
	}
	else
	{
		seek(body, targetPosition, maxSpeed);
	}
}

void SteeringBehaviors::avoid(b2Body* body, const b2Vec2& lookAhead, const std::vector<b2Body*>& rayBodies, float maxSpeed)
{
	for (const auto *rayBody : rayBodies)
	{
		if (const auto* rayBodyData = static_cast<BodyData*>(rayBody->GetUserData()))
		{
			if (rayBodyData->objectType & ObjectType::Obstacle)
			{
				body->ApplyLinearImpulse(desiredVelocity(rayBody->GetPosition(), lookAhead, maxSpeed), body->GetWorldCenter(), true);
			}
		}
	}
}

void SteeringBehaviors::wander(b2Body* body, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float maxSpeed)
{
	auto wanderCenter = body->GetLinearVelocity();
	wanderCenter.Normalize();
	wanderCenter *= wanderDistance;
	wanderCenter += { wanderRadius * std::cos(wanderAngle), wanderRadius * std::sin(wanderAngle) };

	wanderAngle += cocos2d::random() * wanderRate;

	seek(body, body->GetPosition() + wanderCenter, maxSpeed);
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;

	return desiredVelocity;
}