/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PhysicsUtility.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>


namespace Utility
{
	float vectorToRadian(const b2Vec2& vector);
	b2Vec2 radianToVector(float radian);

	float angularImpulseToAngle(float currentAngle, float desiredAngle, float angularVelocity, float inertia);

	float constrainedAngle(float angle);
}