/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CollisionFilter.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>


class CollisionFilter : public b2ContactFilter
{
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
};