/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteerComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>


class SteerComponent
{
public:
	SteerComponent();

	b2Vec2 getSteeringForce() const;
	void setSteeringForce(const b2Vec2& steeringForce);

private:
	b2Vec2 steeringForce;
};