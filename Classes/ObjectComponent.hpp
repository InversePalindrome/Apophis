/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <pugixml.hpp>


class ObjectComponent
{
public:
    ObjectComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    ObjectType getObjectType() const;
    void setObjectType(ObjectType objectType);

private:
    ObjectType objectType;
};