/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ConversionUtility.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/math/Vec2.h>

#include <Box2D/Common/b2Math.h>


namespace Utility
{
	float degreesToRadians(float degrees);
	float radiansToDegrees(float radians);

	b2Vec2 screenToWorldCoordinates(const cocos2d::Vec2& screenCoordinates);
	cocos2d::Vec2 worldToScreenCoordinates(const b2Vec2& worldCoordinates);
}