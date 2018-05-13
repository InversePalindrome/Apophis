/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringBehaviors.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>


namespace SteeringBehaviors
{
	b2Vec2 seek(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float impulse);
	b2Vec2 pursue(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float impulse, float predictionTime = 5.f);
	b2Vec2 arrive(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float impulse, float slowRadius);
    b2Vec2 avoid(const b2Body* body, float avoidanceDistance, float avoidanceForce);
	b2Vec2 wander(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float impulse);

	b2Vec2 align(const b2Body* body, float groupRadius, float impulse, ObjectType groupType);
	b2Vec2 cohesion(const b2Body* body, float groupRadius, float impulse, ObjectType groupType);
	b2Vec2 separate(const b2Body* body,  float groupRadius, float impulse, ObjectType groupType);

	b2Vec2 follow(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float impulse);
	b2Vec2 queue(b2Body* body, const b2Vec2& steeringForce, float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float impulse, ObjectType groupType);
	
	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float impulse);
}