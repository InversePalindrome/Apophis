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

#include <vector>


namespace BodyParser
{
    void parseBody(b2Body* body, const pugi::xml_node& bodyNode);
    void parseFixtureDef(b2FixtureDef& fixtureDef, const pugi::xml_node& fixtureNode);

    void parseCircle(b2CircleShape& circle, const pugi::xml_node& circleNode);
    void parseEdge(b2EdgeShape& edge, const pugi::xml_node& edgeNode);
    void parsePolygon(b2PolygonShape& polygon, const pugi::xml_node& polygonNode);
    void parseChain(b2ChainShape& chain, const pugi::xml_node& chainNode);

    void parseVertices(std::vector<b2Vec2>& vertices, const pugi::xml_node& verticesNode);
}
