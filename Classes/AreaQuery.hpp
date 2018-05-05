/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AreaQuery.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include <vector>


struct AreaQuery : public b2QueryCallback
{
	virtual bool ReportFixture(b2Fixture* fixture) override;

	std::vector<b2Body*> queryBodies;
};