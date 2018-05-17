/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringBehaviors.cpp
InversePalindrome.com
*/


#include "BodyData.hpp"
#include "AreaQuery.hpp"
#include "RayCastQuery.hpp"
#include "PhysicsUtility.hpp"
#include "SteeringBehaviors.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <cocos/base/ccRandom.h>


b2Vec2 SteeringBehaviors::seek(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float impulse)
{
	return desiredVelocity(bodyPosition, targetPosition, impulse) - bodyVelocity;
}

b2Vec2 SteeringBehaviors::pursue(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float impulse, float predictionTime)
{
	auto distance = (targetPosition - bodyPosition).Length();

	if (bodyVelocity.Length() > distance / predictionTime)
	{
		predictionTime = distance / bodyVelocity.Length();
	}

	const auto& futurePosition = targetPosition + predictionTime * targetVelocity;

	return seek(bodyPosition, futurePosition, bodyVelocity, impulse);
}

b2Vec2 SteeringBehaviors::arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float impulse, float slowRadius)
{
	auto radius = (targetPosition - bodyPosition).Length();
	
	if (radius < slowRadius)
	{
		return seek(bodyPosition, targetPosition, bodyVelocity, impulse * radius / slowRadius);
	}

	return seek(bodyPosition, targetPosition, bodyVelocity, impulse);
}

b2Vec2 SteeringBehaviors::avoid(const b2Body* body, float avoidanceDistance, float avoidanceForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto ahead = body->GetLinearVelocity();
	ahead.Normalize();
	ahead *= avoidanceDistance;
	ahead += body->GetPosition();

	if ((body->GetPosition() - ahead).LengthSquared() > 0.0f)
	{
		RayCastQuery rayQuery;

		body->GetWorld()->RayCast(&rayQuery, body->GetPosition(), ahead);

		for (const auto& rayData : rayQuery.queryData)
		{
			if (const auto* rayBodyData = static_cast<BodyData*>(rayData.body->GetUserData()))
			{
				if (rayBodyData->objectType & ObjectType::Obstacle)
				{
					steeringForce += desiredVelocity(rayData.body->GetPosition(), ahead, avoidanceForce);
					break;
				}
			}
		}
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::wander(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float impulse)
{
	auto wanderCenter = bodyVelocity;
	wanderCenter.Normalize();
	wanderCenter *= wanderDistance;
	wanderCenter += { wanderRadius * std::cos(wanderAngle), wanderRadius * std::sin(wanderAngle) };

	wanderAngle += cocos2d::random() * wanderRate;

	return seek(bodyPosition, bodyPosition + wanderCenter, bodyVelocity, impulse);
}

b2Vec2 SteeringBehaviors::align(const b2Body* body, float groupRadius, float impulse, ObjectType groupType)
{
	b2Vec2 steeringForce(0.f, 0.f);

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
				if (neighborBodyData->objectType & groupType)
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
		alignForce *= impulse;

		steeringForce += alignForce;
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::cohesion(const b2Body* body, float groupRadius, float impulse, ObjectType groupType)
{
	b2Vec2 steeringForce(0.f, 0.f);

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
				if (neighborBodyData->objectType & groupType)
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
		cohesionForce *= impulse;

		steeringForce += cohesionForce;
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::separate(const b2Body* body, float groupRadius, float impulse, ObjectType groupType)
{
	b2Vec2 steeringForce(0.f, 0.f);

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
				if (neighborBodyData->objectType & groupType)
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
		separationForce *= impulse;

		steeringForce += separationForce;
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::follow(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float impulse)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto leaderDirection = leaderVelocity;
	leaderDirection.Normalize();
	leaderDirection *= distanceFromLeader;

	auto leaderAhead = leaderPosition + leaderDirection;

	if ((bodyPosition - leaderAhead).Length() <= leaderSight || (bodyPosition - leaderPosition).Length() <= leaderSight)
	{
		steeringForce += pursue(bodyPosition, leaderPosition, bodyVelocity, leaderVelocity, -impulse);
	}

	steeringForce += arrive(bodyPosition, leaderPosition - leaderDirection, bodyVelocity, impulse, distanceFromLeader);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::queue(b2Body* body, const b2Vec2& steeringForce, float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float impulse, ObjectType groupType)
{
	b2Vec2 queueForce(0.f, 0.f);

	auto ahead = body->GetLinearVelocity();
	ahead.Normalize();
	ahead *= queueDistance;
	ahead += body->GetPosition();

	if ((body->GetPosition() - ahead).LengthSquared() > 0.0f)
	{
		RayCastQuery rayQuery;

		body->GetWorld()->RayCast(&rayQuery, body->GetPosition(), body->GetPosition() + ahead);

		for (const auto& rayData : rayQuery.queryData)
		{
			if (const auto* rayBodyData = static_cast<BodyData*>(rayData.body->GetUserData()))
			{
				if (rayBodyData->objectType & groupType)
				{
			     	queueForce = -steeringBrakeFactor * steeringForce;
				    queueForce -= body->GetLinearVelocity();
					queueForce += separate(body, groupRadius, impulse, groupType);

					body->SetLinearVelocity({ body->GetLinearVelocity().x * shrinkFactor, body->GetLinearVelocity().y * shrinkFactor });

					break;
				}
			}
		}
	}

	return queueForce;
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float impulse)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= impulse;

	return desiredVelocity;
}