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
	void pursue(b2Body* body, const b2Vec2& targetPosition, const b2Vec2& targetVelocity, float maxSpeed, float predictionTime);
	void arrive(b2Body* body, const b2Vec2& targetPosition, float maxSpeed, float slowRadius);
    void avoid(b2Body* body, const b2Vec2& targetPosition, const std::vector<b2Body*>& bodies, float maxSpeed);
	void wander(b2Body* body, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float maxSpeed);
	
	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float maxSpeed);
}