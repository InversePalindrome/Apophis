/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AreaQuery.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include <entityx/Entity.h>

#include <vector>


struct AreaQuery : public b2QueryCallback
{
	virtual bool ReportFixture(b2Fixture* fixture) override;

	std::vector<entityx::Entity*> queryEntities;
};