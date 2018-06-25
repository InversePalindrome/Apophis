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

#include <variant>


namespace BodyParser
{
	b2BodyDef createBodyDef(const pugi::xml_node& bodyNode);
	b2FixtureDef createFixtureDef(const pugi::xml_node& fixtureNode);
	b2CircleShape createCircle(const pugi::xml_node& circleNode);
	b2PolygonShape createRectangle(const pugi::xml_node& rectangleNode);
	b2PolygonShape createPolygon(const pugi::xml_node& polygonNode);

	std::variant<b2CircleShape, b2PolygonShape> createShape(const pugi::xml_node& shapeNode);
}
