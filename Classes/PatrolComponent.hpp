/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class PatrolComponent
{
public:
    PatrolComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    int getPathwayID() const;
    void setPathwayID(int pathwayID);

    int getCurrentPointIndex() const;
    void setCurrentPointIndex(int currentPointIndex);

private:
    int pathwayID;
    int currentPointIndex;
};