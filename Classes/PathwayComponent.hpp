/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PathwayComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <pugixml.hpp>

#include <vector>


class PathwayComponent
{
public:
    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    void addPathwayPoint(const b2Vec2& pathwayPoint);

    void removePathwayPoint(std::size_t pathwayPointIndex);
    void clearPathwayPoints();

    std::size_t getPathwayPointsCount() const;

    bool hasPathwayPoints() const;

    b2Vec2& operator[](std::size_t pathwayPointIndex);
    const b2Vec2& operator[](std::size_t pathwayPointIndex) const;

    std::vector<b2Vec2>::iterator begin();
    std::vector<b2Vec2>::iterator end();

    std::vector<b2Vec2>::const_iterator begin() const;
    std::vector<b2Vec2>::const_iterator end() const;

private:
    std::vector<b2Vec2> pathwayPoints;
};