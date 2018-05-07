/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringBehaviors.cpp
InversePalindrome.com
*/


#include "BodyData.hpp"
#include "AreaQuery.hpp"
#include "RayCastQuery.hpp"
#include "PhysicsUtility.hpp"
#include "SteeringBehaviors.hpp"

#include <Box2D/Dynamics/b2World.h>

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

void SteeringBehaviors::avoid(b2Body* body, float avoidanceDistance, float avoidanceForce)
{
	auto lookAhead = body->GetLinearVelocity();
	lookAhead.Normalize();
	lookAhead *= avoidanceDistance;

	RayCastQuery rayQuery;

	body->GetWorld()->RayCast(&rayQuery, body->GetPosition(), body->GetPosition() + lookAhead);

	for (const auto *rayBody : rayQuery.queryBodies)
	{
		if (const auto* rayBodyData = static_cast<BodyData*>(rayBody->GetUserData()))
		{
			if (rayBodyData->objectType & ObjectType::Obstacle)
			{
				body->ApplyLinearImpulse(desiredVelocity(rayBody->GetPosition(), lookAhead, avoidanceForce), body->GetWorldCenter(), true);
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

void SteeringBehaviors::align(b2Body* body, float groupRadius, float maxSpeed)
{
	if (const auto* bodyData = static_cast<BodyData*>(body->GetUserData()))
	{
		AreaQuery areaQuery;

		b2AABB groupArea;
		groupArea.lowerBound = { body->GetPosition().x - groupRadius, body->GetPosition().y - groupRadius };
		groupArea.upperBound = { body->GetPosition().x + groupRadius, body->GetPosition().y + groupRadius };

		body->GetWorld()->QueryAABB(&areaQuery, groupArea);

		b2Vec2 alignForce(0.f, 0.f);
		std::size_t groupCount = 0u;

		for (const auto* neighborBody : areaQuery.queryBodies)
		{
			if (body != neighborBody)
			{
				if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
				{
					if (neighborBodyData->objectType & bodyData->objectType)
					{
						alignForce += neighborBody->GetLinearVelocity();
						++groupCount;
					}
				}
			}
		}

		if (groupCount > 0u)
		{
			alignForce *= 1 / groupCount;
			alignForce.Normalize();
			alignForce *= maxSpeed;

			body->ApplyLinearImpulse(alignForce, body->GetWorldCenter(), true);
		}
	}
}

void SteeringBehaviors::cohesion(b2Body* body, float groupRadius, float maxSpeed)
{
	if (const auto* bodyData = static_cast<BodyData*>(body->GetUserData()))
	{
		AreaQuery areaQuery;

		b2AABB groupArea;
		groupArea.lowerBound = { body->GetPosition().x - groupRadius, body->GetPosition().y - groupRadius };
		groupArea.upperBound = { body->GetPosition().x + groupRadius, body->GetPosition().y + groupRadius };

		body->GetWorld()->QueryAABB(&areaQuery, groupArea);

		b2Vec2 cohesionForce(0.f, 0.f);
		std::size_t groupCount = 0u;

		for (const auto* neighborBody : areaQuery.queryBodies)
		{
			if (body != neighborBody)
			{
				if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
				{
					if (neighborBodyData->objectType & bodyData->objectType)
					{
						cohesionForce += neighborBody->GetPosition();
						++groupCount;
					}
				}
			}
		}

		if (groupCount > 0u)
		{
			cohesionForce *= 1 / groupCount;
			cohesionForce -= body->GetPosition();
			cohesionForce.Normalize();
			cohesionForce *= maxSpeed;

			body->ApplyLinearImpulse(cohesionForce, body->GetWorldCenter(), true);
		}
	}
}

void SteeringBehaviors::separate(b2Body* body, float groupRadius, float maxSpeed)
{
	if (const auto* bodyData = static_cast<BodyData*>(body->GetUserData()))
	{
		AreaQuery areaQuery;

		b2AABB groupArea;
		groupArea.lowerBound = { body->GetPosition().x - groupRadius, body->GetPosition().y - groupRadius };
		groupArea.upperBound = { body->GetPosition().x + groupRadius, body->GetPosition().y + groupRadius };

		body->GetWorld()->QueryAABB(&areaQuery, groupArea);

		b2Vec2 separationForce(0.f, 0.f);
		std::size_t groupCount = 0u;

		for (const auto* neighborBody : areaQuery.queryBodies)
		{
			if (body != neighborBody)
			{
				if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
				{
					if (neighborBodyData->objectType & bodyData->objectType)
					{
						separationForce += body->GetPosition() - neighborBody->GetPosition();
						++groupCount;
					}
				}
			}
		}

		if (groupCount > 0u)
		{
			separationForce *= -1 / groupCount;
			separationForce.Normalize();
			separationForce *= maxSpeed;

			body->ApplyLinearImpulse(separationForce, body->GetWorldCenter(), true);
		}
	}
}

void SteeringBehaviors::follow(b2Body* body, const b2Vec2& targetPosition, const b2Vec2& targetVelocity, float distanceFromLeader, float maxSpeed)
{
	auto leaderDirection = targetVelocity;
	leaderDirection.Normalize();
	leaderDirection *= distanceFromLeader;

	for (const auto* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2RayCastOutput output;

		if (fixture->RayCast(&output, { targetPosition, targetPosition + leaderDirection, 1.f}, 0))
		{
			pursue(body, targetPosition, targetVelocity, -maxSpeed);
		}
	}

	arrive(body, targetPosition - leaderDirection, maxSpeed, distanceFromLeader);
}

void SteeringBehaviors::queue(b2Body* body, float groupRadius, float queueDistance, float shrinkFactor, float maxSpeed)
{
	if (const auto* bodyData = static_cast<BodyData*>(body->GetUserData()))
	{
		auto ahead = body->GetLinearVelocity();
		ahead.Normalize();
		ahead *= queueDistance;

		RayCastQuery rayQuery;

		body->GetWorld()->RayCast(&rayQuery, body->GetPosition(), body->GetPosition() + ahead);

		for (const auto *rayBody : rayQuery.queryBodies)
		{
			if (const auto* rayBodyData = static_cast<BodyData*>(rayBody->GetUserData()))
			{
				if (rayBodyData->objectType & bodyData->objectType)
				{
					body->SetLinearVelocity({ body->GetLinearVelocity().x * shrinkFactor, body->GetLinearVelocity().y * shrinkFactor });

					separate(body, groupRadius, maxSpeed);

					break;
				}
			}
		}
	}
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;

	return desiredVelocity;
}