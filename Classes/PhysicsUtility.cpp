/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PhysicsUtility.cpp
InversePalindrome.com
*/


#include "PhysicsUtility.hpp"

#include <cocos/base/ccMacros.h>

#include <cmath>


float Utility::vectorToRadian(const b2Vec2& vector)
{
	return std::atan2f(vector.x, vector.y);
}

b2Vec2 Utility::radianToVector(float radian)
{
	return { std::cos(radian), std::sin(radian) };
}

float Utility::angularImpulseToAngle(float currentAngle, float desiredAngle, float angularVelocity, float inertia)
{
	auto nextAngle = currentAngle + angularVelocity / FPS;
	auto totalRotation = constrainedAngle(desiredAngle - nextAngle);
	
	auto desiredAngularVelocity = totalRotation * FPS;;
	auto impulse = inertia * desiredAngularVelocity;

	return impulse;
}

float Utility::constrainedAngle(float angle)
{
	return std::remainderf(angle, 2 * PI);
}