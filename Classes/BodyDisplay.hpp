/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyDisplay.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <vector>


namespace BodyDisplay
{
    void displayBody(b2Body* body);
    void displayFixture(b2Fixture* fixture);

    void displayCircle(b2CircleShape& circle);
    void displayCircle(const b2CircleShape* circle);

    void displayEdge(b2EdgeShape& edge);
    void displayEdge(const b2EdgeShape* edge);

    void displayPolygon(b2PolygonShape& polygon, int& polygonModeIndex, std::vector<b2Vec2>& vertices, b2Vec2& box);
    void displayPolygon(const b2PolygonShape* polygon);

    void displayChain(b2ChainShape& chain, int& chainModeIndex, std::vector<b2Vec2>& vertices);
    void displayChain(const b2ChainShape* chain);

    void displayBox(b2Vec2& box);
    void displayVertices(std::vector<b2Vec2>& vertices);
}