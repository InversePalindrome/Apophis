/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringBehaviors.hpp
InversePalindrome.com
*/


#pragma once

#include <vector>

#include <Box2D/Common/b2Math.h>


namespace SteeringBehaviors
{
	b2Vec2 seek(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float maxSpeed);
	b2Vec2 pursue(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float maxSpeed);
	b2Vec2 arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float maxSpeed);
	b2Vec2 follow(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float maxSpeed);
	b2Vec2 wander(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float maxSpeed);
	b2Vec2 orbit(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, const b2Vec2& bodyVelocity, float maxSpeed);

	b2Vec2 avoidForce(const std::vector<b2Vec2>& neighborPositions);
	b2Vec2 alignForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborVelocities);
	b2Vec2 cohesionForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions);
	b2Vec2 separateForce(const b2Vec2& agentPosition, const std::vector<b2Vec2>& neighborPositions, float separationRadius);

	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed);

	float face(float desiredAngle, float bodyAngle, float bodyAngularVelocity, float bodyInertia);
	float face(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia);
}