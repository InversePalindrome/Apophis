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
	const auto distance = (targetPosition - bodyPosition).Length();

	if (bodyVelocity.Length() > distance / predictionTime)
	{
		predictionTime = distance / bodyVelocity.Length();
	}

	return seek(bodyPosition, targetPosition + predictionTime * targetVelocity, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float maxSpeed)
{
	if (const auto radius = (targetPosition - bodyPosition).Length(); radius < slowRadius)
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

	if ((bodyPosition - leaderPosition + leaderDirection).Length() <= leaderSight || (bodyPosition - leaderPosition).Length() <= leaderSight)
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

b2Vec2 SteeringBehaviors::orbit(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, const b2Vec2& bodyVelocity, float maxSpeed)
{
	const auto radius = primaryPosition - satellitePosition;

	auto steeringForce = radius.Skew();
	steeringForce.Normalize();
	steeringForce *= maxSpeed;

	return steeringForce - bodyVelocity;
}

b2Vec2 SteeringBehaviors::avoidForce(const std::vector<b2Vec2>& neighborPositions)
{
	b2Vec2 avoidForce(0.f, 0.f);

	for (const auto& bodyPosition : neighborPositions)
	{

	}

	return avoidForce;
}

b2Vec2 SteeringBehaviors::alignForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborVelocities)
{
	b2Vec2 alignForce(0.f, 0.f);

	for (const auto& neighborVelocity : neighborVelocities)
	{
		alignForce += neighborVelocity;
	}

	alignForce *= 1.f / neighborVelocities.size();
	alignForce.Normalize();

	return alignForce;
}

b2Vec2 SteeringBehaviors::cohesionForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions)
{
	b2Vec2 cohesionForce(0.f, 0.f);

	for (const auto& neighborPosition : neighborPositions)
	{
		cohesionForce += neighborPosition;
	}

	cohesionForce *= 1.f / neighborPositions.size();
	cohesionForce -= agentPosition;
	cohesionForce.Normalize();

	return cohesionForce;
}
b2Vec2 SteeringBehaviors::separateForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions, float separationRadius)
{
	b2Vec2 separateForce(0.f, 0.f);

	for (const auto& neighborPosition : neighborPositions)
	{
		separateForce += neighborPosition - agentPosition;
	}

	separateForce *= -1.f / neighborPositions.size();
	separateForce.Normalize();

	return separateForce;
}

b2Vec2 SteeringBehaviors::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;

	return desiredVelocity;
}

float SteeringBehaviors::face(float desiredAngle, float bodyAngle, float bodyAngularVelocity, float bodyInertia)
{
	const auto nextAngle = bodyAngle + bodyAngularVelocity / Constants::FPS;

	const auto totalRotation = std::remainderf(desiredAngle - nextAngle, 2 * boost::math::constants::pi<float>());

	return bodyInertia * totalRotation * Constants::FPS;
}

float SteeringBehaviors::face(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia)
{
	const auto desiredAngle = std::atan2f(targetPosition.y - bodyPosition.y, targetPosition.x - bodyPosition.x);

	return face(desiredAngle, bodyAngle, bodyAngularVelocity, bodyInertia);
}
	