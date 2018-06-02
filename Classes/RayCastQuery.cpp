/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RayCastQuery.cpp
InversePalindrome.com
*/


#include "RayCastQuery.hpp"

#include <entityx/Entity.h>


float RayCastQuery::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
	queryData.insert({ static_cast<entityx::Entity*>(fixture->GetBody()->GetUserData()), point, normal, fraction });

	return 1.f;
}
