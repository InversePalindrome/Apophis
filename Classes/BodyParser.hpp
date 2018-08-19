/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyParser.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <pugixml.hpp>


namespace BodyParser
{
	void parseBody(b2Body* body, const pugi::xml_node& bodyNode);
	void parseFixtureDef(b2FixtureDef& fixtureDef, const pugi::xml_node& fixtureNode);
	void parseCircleShape(b2CircleShape& circle, const pugi::xml_node& circleNode);
	void parseEdgeShape(b2EdgeShape& edge, const pugi::xml_node& edgeNode);
	void parsePolygonShape(b2PolygonShape& polygon, const pugi::xml_node& polygonNode);
	void parseChainShape(b2ChainShape& chain, const pugi::xml_node& chainNode);
}
