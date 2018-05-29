/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringBehaviors.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "AreaQuery.hpp"
#include "RayCastQuery.hpp"
#include "ObjectComponent.hpp"
#include "SteeringBehaviors.hpp"

#include <entityx/Entity.h>

#include <cocos/base/ccRandom.h>

#include <boost/math/constants/constants.hpp>

#include <cmath>


b2Vec2 SteeringBehaviors::seekForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force)
{
	return desiredVelocity(bodyPosition, targetPosition, force) - bodyVelocity;
}

b2Vec2 SteeringBehaviors::pursueForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float force)
{
	auto distance = (targetPosition - bodyPosition).Length();

	if (bodyVelocity.Length() > distance / predictionTime)
	{
		predictionTime = distance / bodyVelocity.Length();
	}

	return seekForce(bodyPosition, targetPosition + predictionTime * targetVelocity, bodyVelocity, force);
}

b2Vec2 SteeringBehaviors::arriveForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force, float slowRadius)
{
	auto radius = (targetPosition - bodyPosition).Length();

	if (radius < slowRadius)
	{
		return seekForce(bodyPosition, targetPosition, bodyVelocity, force * radius / slowRadius);
	}

	return seekForce(bodyPosition, targetPosition, bodyVelocity, force);
}

b2Vec2 SteeringBehaviors::followForce(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto leaderDirection = leaderVelocity;
	leaderDirection.Normalize();
	leaderDirection *= distanceFromLeader;

	auto leaderAhead = leaderPosition + leaderDirection;

	if ((bodyPosition - leaderAhead).Length() <= leaderSight || (bodyPosition - leaderPosition).Length() <= leaderSight)
	{
		steeringForce += pursueForce(bodyPosition, leaderPosition, bodyVelocity, leaderVelocity, predictionTime, -force);
	}

	steeringForce += arriveForce(bodyPosition, leaderPosition - leaderDirection, bodyVelocity, distanceFromLeader, force);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::wanderForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float force)
{
	auto wanderCenter = bodyVelocity;
	wanderCenter.Normalize();
	wanderCenter *= wanderDistance;
	wanderCenter += { wanderRadius * std::cos(wanderAngle), wanderRadius * std::sin(wanderAngle) };

	wanderAngle += cocos2d::rand_minus1_1() * wanderRate;

	return seekForce(bodyPosition, bodyPosition + wanderCenter, bodyVelocity, force);
}

b2Vec2 SteeringBehaviors::avoidForce(b2World* world, const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float avoidanceDistance, float avoidanceForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto ahead = bodyVelocity;
	ahead.Normalize();
	ahead *= avoidanceDistance;
	ahead += bodyPosition;

	if ((bodyPosition - ahead).LengthSquared() > 0.0f)
	{
		RayCastQuery rayQuery;

		world->RayCast(&rayQuery, bodyPosition, ahead);

		for (const auto& rayData : rayQuery.queryData)
		{
			if (auto object = static_cast<entityx::Entity*>(rayData.body->GetUserData())->component<ObjectComponent>())
			{
				if (object->getObjectType() & ObjectType::Obstacle)
				{
					steeringForce += desiredVelocity(rayData.body->GetPosition(), ahead, avoidanceForce);
					break;
				}
			}
		}
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::orbitForce(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, float force)
{
	auto radius = primaryPosition - satellitePosition;

	auto steeringForce = radius.Skew();
	steeringForce.Normalize();
	steeringForce *= force;

	return steeringForce;
}

b2Vec2 SteeringBehaviors::alignForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::cohesionForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::separateForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::queueForce(float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float force)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= force;

	return desiredVelocity;
}

float SteeringBehaviors::faceForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia)
{
	auto desiredAngle = std::atan2f(targetPosition.x - bodyPosition.x, targetPosition.y - bodyPosition.y);
	auto nextAngle = bodyAngle + bodyAngularVelocity / Constants::FPS;

	auto totalRotation = std::remainderf(desiredAngle - nextAngle, 2 * boost::math::constants::pi<float>());

	auto desiredAngularVelocity = totalRotation * Constants::FPS;

	return bodyInertia * desiredAngularVelocity;
}