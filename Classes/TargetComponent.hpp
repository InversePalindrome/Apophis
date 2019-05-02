/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TargetComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class TargetComponent
{
public:
    TargetComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    int getTargetID() const;
    void setTargetID(int targetID);

private:
    int targetID;
};