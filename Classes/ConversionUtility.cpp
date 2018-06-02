/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ConversionUtility.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "ConversionUtility.hpp"

#include <boost/math/constants/constants.hpp>


float Utility::degreesToRadians(float degrees)
{
	return degrees * boost::math::constants::pi<float>() / 180.f;
}

float Utility::radiansToDegrees(float radians)
{
	return radians * 180.f / boost::math::constants::pi<float>();
}

b2Vec2 Utility::screenToWorldCoordinates(const cocos2d::Vec2& screenCoordinates)
{
	return { screenCoordinates.x / Constants::PTM_RATIO, screenCoordinates.y / Constants::PTM_RATIO };
}

cocos2d::Vec2 Utility::worldToScreenCoordinates(const b2Vec2& worldCoordinates)
{
	return { worldCoordinates.x * Constants::PTM_RATIO, worldCoordinates.y * Constants::PTM_RATIO };
}