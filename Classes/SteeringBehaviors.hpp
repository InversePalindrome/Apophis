/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringBehaviors.hpp
InversePalindrome.com
*/


#pragma once


#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

#include <vector>


namespace SteeringBehaviors
{
	void seek(b2Body* body, const b2Vec2& targetPosition, float maxSpeed);
	void pursue(b2Body* body, const b2Vec2& targetPosition, const b2Vec2& targetVelocity, float maxSpeed = 10.f, float predictionTime = 5.f);
	void arrive(b2Body* body, const b2Vec2& targetPosition, float maxSpeed = 10.f, float slowRadius = 5.f);
    void avoid(b2Body* body, float avoidanceDistance = 5.f, float avoidanceForce = 10.f);
	void wander(b2Body* body, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float maxSpeed = 10.f);

	void align(b2Body* body, float groupRadius = 1.f, float maxSpeed = 10.f);
	void cohesion(b2Body* body, float groupRadius = 1.f, float maxSpeed = 10.f);
	void separate(b2Body* body,  float groupRadius = 1.f, float maxSpeed = 10.f);

	void follow(b2Body* body, const b2Vec2& targetPosition, const b2Vec2& targetVelocity, float distanceFromLeader = 5.f, float maxSpeed = 10.f);
	void queue(b2Body* body,  float groupRadius = 5.f, float queueDistance = 1.f, float shrinkFactor = 0.3f, float maxSpeed = 10.f);
	
	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed = 10.f);
}