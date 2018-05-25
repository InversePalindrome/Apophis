/*
Copyright (c) 2018 Inverse Palindrome
Apophis - MathUtility.cpp
InversePalindrome.com
*/


#include "MathUtility.hpp"

#include <boost/math/constants/constants.hpp>


float Utility::degreesToRadians(float degrees)
{
	return degrees * boost::math::constants::pi<float>() / 180.f;
}

float Utility::radiansToDegrees(float radians)
{
	return radians * 180.f / boost::math::constants::pi<float>();
}