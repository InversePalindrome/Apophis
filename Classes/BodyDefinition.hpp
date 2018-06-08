/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - BodyDefinition.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <vector>
#include <variant>


struct BodyDefinition
{
	b2BodyDef bodyDef;
	std::vector<std::pair<b2FixtureDef, std::variant<b2CircleShape, b2PolygonShape>>> fixtureDefs;
};