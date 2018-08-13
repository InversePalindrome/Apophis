/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodySerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>


#include <pugixml.hpp>


namespace BodySerializer
{
	void saveBody(const b2Body* body, pugi::xml_node& bodyNode);
	void saveFixture(const b2Fixture* fixture, pugi::xml_node& fixtureNode);

	void saveCircle(const b2CircleShape* circle, pugi::xml_node& circleNode);
	void saveEdge(const b2EdgeShape* edge, pugi::xml_node& edgeNode);
	void savePolygon(const b2PolygonShape* polygon, pugi::xml_node& polygonNode);
	void saveChain(const b2ChainShape* chain, pugi::xml_node& chainNode);
}