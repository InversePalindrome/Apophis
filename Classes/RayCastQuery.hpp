/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RayCastQuery.hpp
InversePalindrome.com
*/


#pragma once

#include "RayCastData.hpp"

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include <set>


struct RayCastQuery : public b2RayCastCallback
{
    virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    std::set<RayCastData> queryData;
};