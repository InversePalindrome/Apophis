/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - RayCastData.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>


struct RayCastData
{
	b2Body* body;
	b2Vec2 point;
	b2Vec2 normal;
	float fraction;
};

bool operator<(const RayCastData& rayCastData1, const RayCastData& rayCastData2);