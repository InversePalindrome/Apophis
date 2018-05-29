/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringBehaviors.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>


namespace SteeringBehaviors
{
	b2Vec2 seekForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force);
	b2Vec2 pursueForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float force);
	b2Vec2 arriveForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float force);
	b2Vec2 followForce(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float force);
	b2Vec2 wanderForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float force);
	b2Vec2 avoidForce(b2World* world, const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float avoidanceDistance, float avoidanceForce);
	b2Vec2 orbitForce(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, float force);

	b2Vec2 alignForce(float groupRadius, float force);
	b2Vec2 cohesionForce(float groupRadius, float force);
	b2Vec2 separateForce(float groupRadius, float force);
	b2Vec2 queueForce(float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float force);

	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float force);

	float faceForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia);
}