/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - RayCastQuery.cpp
InversePalindrome.com
*/


#include "RayCastQuery.hpp"


float RayCastQuery::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
	queryBodies.push_back(fixture->GetBody());

	return 1.f;
}
