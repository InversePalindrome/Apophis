/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AreaQuery.cpp
InversePalindrome.com
*/


#include "AreaQuery.hpp"


bool AreaQuery::ReportFixture(b2Fixture* fixture)
{
	queryBodies.push_back(fixture->GetBody());

	return true;
}