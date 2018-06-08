/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - BodyParser.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <tinyxml2/tinyxml2.h>


namespace BodyParser
{
	b2BodyDef createBodyDef(const tinyxml2::XMLElement* bodyNode);
	b2FixtureDef createFixtureDef(const tinyxml2::XMLElement* fixtureNode);
	b2CircleShape createCircle(const tinyxml2::XMLElement* shapeNode);
	b2PolygonShape createPolygon(const tinyxml2::XMLElement* shapeNode);
}