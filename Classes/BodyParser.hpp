/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyParser.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <pugixml.hpp>


namespace BodyParser
{
	void parseBodyDef(b2BodyDef& bodyDef, const pugi::xml_node& bodyNode);
    void parseFixtureDef(b2FixtureDef& fixtureDef, const pugi::xml_node& fixtureNode);
	void parseCircleShape(b2CircleShape& circleDef, const pugi::xml_node& circleNode);
	void parseRectangleShape(b2PolygonShape& rectangleShape, const pugi::xml_node& rectangleNode);
	void parsePolygonShape(b2PolygonShape& polygonShape, const pugi::xml_node& polygonNode);
}
