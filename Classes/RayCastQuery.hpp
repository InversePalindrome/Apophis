/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - RayCastQuery.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include <vector>


struct RayCastQuery : public b2RayCastCallback
{
	virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

	std::vector<b2Body*> queryBodies;
};