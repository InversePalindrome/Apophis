/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AreaQuery.cpp
InversePalindrome.com
*/


#include "AreaQuery.hpp"


bool AreaQuery::ReportFixture(b2Fixture* fixture)
{
    queryEntities.push_back(static_cast<entityx::Entity*>(fixture->GetBody()->GetUserData()));

    return true;
}