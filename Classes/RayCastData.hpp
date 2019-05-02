/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RayCastData.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <entityx/Entity.h>


struct RayCastData
{
    entityx::Entity* entity;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
};

bool operator<(const RayCastData& rayCastData1, const RayCastData& rayCastData2);