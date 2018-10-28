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

b2Vec2 SteeringBehaviors::flee(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float maxSpeed)
{
	return desiredVelocity(targetPosition, bodyPosition, maxSpeed) - bodyVelocity;
}

b2Vec2 SteeringBehaviors::pursue(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float maxSpeed)
{
	const auto predictionFrames = (targetPosition - bodyPosition).Length() / maxSpeed;

	return seek(bodyPosition, targetPosition + predictionFrames * targetVelocity, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::evade(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float maxSpeed)
{
	const auto predictionFrames = (targetPosition - bodyPosition).Length() / maxSpeed;

	return flee(bodyPosition, targetPosition + predictionFrames * targetVelocity, bodyVelocity, maxSpeed);
}

b2Vec2 SteeringBehaviors::arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float maxSpeed)
{
	if (const auto radius = (targetPosition - bodyPosition).Length(); radius < slowRadius)
	{
		return seek(bodyPosition, targetPosition, bodyVelocity, maxSpeed * radius / slowRadius);
	}

	return seek(bodyPosition, targetPosition, bodyVelocity, maxSpeed);
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

b2Vec2 SteeringBehaviors::alignForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborVelocities, float alignmentForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	for (const auto& neighborVelocity : neighborVelocities)
	{
		steeringForce += neighborVelocity;
	}

	if (!neighborVelocities.empty())
	{
		steeringForce *= 1.f / neighborVelocities.size();
		steeringForce.Normalize();
		steeringForce *= alignmentForce;
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::cohesionForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions, float cohesionForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	for (const auto& neighborPosition : neighborPositions)
	{
		steeringForce += neighborPosition;
	}

	if (!neighborPositions.empty())
	{
		steeringForce *= 1.f / neighborPositions.size();
		steeringForce -= agentPosition;
		steeringForce.Normalize();
		steeringForce *= cohesionForce;
	}

	return steeringForce;
}

b2Vec2 SteeringBehaviors::separateForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions, float separationForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	for (const auto& neighborPosition : neighborPositions)
	{
		steeringForce += neighborPosition - agentPosition;
	}

	if (!neighborPositions.empty())
	{
		steeringForce *= -1.f / neighborPositions.size();
		steeringForce.Normalize();
		steeringForce *= separationForce;
	}
	
	return steeringForce;
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
	