/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteerForce.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>


class SteerForce
{
public:
	b2Vec2 getSteeringForce() const;
	void setSteeringForce(const b2Vec2& steeringForce);

private:
	b2Vec2 steeringForce{ 0.f, 0.f };
};