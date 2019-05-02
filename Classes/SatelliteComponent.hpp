/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class SatelliteComponent
{
public:
    SatelliteComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    int getPrimaryID() const;
    void setPrimaryID(int primaryID);

    int getOrbitDirection() const;
    void setOrbitDirection(int orbitDirection);

private:
    int primaryID;
    int orbitDirection;
};