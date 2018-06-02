/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringBehaviors.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "SteeringBehaviors.hpp"

#include <cocos/base/ccRandom.h>

#include <boost/math/constants/constants.hpp>

#include <cmath>


b2Vec2 SteeringBehaviors::seek(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float maxSpeed)
{
	return desiredVelocity(bodyPosition, targetPosition, maxSpeed) - bodyVelocity;
}

b2Vec2 SteeringBehaviors::pursue(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float maxSpeed)
{
	auto distance = (targetPosition - bodyPosition).Length();

	if (bodyVelocity.Length() > distance / predictionTime)
	{
		predictionTime = distance / bodyVelocity.Length();
	}

	return seek(bodyPosition, targetPosition + predictionTime * targetVelocity, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float maxSpeed)
{
	auto radius = (targetPosition - bodyPosition).Length();

	if (radius < slowRadius)
	{
		return seek(bodyPosition, targetPosition, bodyVelocity, maxSpeed * radius / slowRadius);
	}

	return seek(bodyPosition, targetPosition, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::follow(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float maxSpeed)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto leaderDirection = leaderVelocity;
	leaderDirection.Normalize();
	leaderDirection *= distanceFromLeader;

	auto leaderAhead = leaderPosition + leaderDirection;

	if ((bodyPosition - leaderAhead).Length() <= leaderSight || (bodyPosition - leaderPosition).Length() <= leaderSight)
	{
		steeringForce += pursue(bodyPosition, leaderPosition, bodyVelocity, leaderVelocity, predictionTime, -maxSpeed);
	}

	steeringForce += arrive(bodyPosition, leaderPosition - leaderDirection, bodyVelocity, distanceFromLeader, maxSpeed);

	return steeringForce;
}

b2Vec2 SteeringBehaviors::wander(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float maxSpeed)
{
	auto wanderCenter = bodyVelocity;
	wanderCenter.Normalize();
	wanderCenter *= wanderDistance;
	wanderCenter += { wanderRadius * std::cos(wanderAngle), wanderRadius * std::sin(wanderAngle) };

	wanderAngle += cocos2d::rand_minus1_1() * wanderRate;

	return seek(bodyPosition, bodyPosition + wanderCenter, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::orbit(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, float maxSpeed)
{
	auto radius = primaryPosition - satellitePosition;

	auto steeringForce = radius.Skew();
	steeringForce.Normalize();
	steeringForce *= maxSpeed;

	return steeringForce;
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;

	return desiredVelocity;
}

float SteeringBehaviors::face(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia)
{
	auto desiredAngle = std::atan2f(targetPosition.x - bodyPosition.x, targetPosition.y - bodyPosition.y);
	auto nextAngle = bodyAngle + bodyAngularVelocity / Constants::FPS;

	auto totalRotation = std::remainderf(desiredAngle - nextAngle, 2 * boost::math::constants::pi<float>());

	auto desiredAngularVelocity = totalRotation * Constants::FPS;

	return bodyInertia * desiredAngularVelocity;
}