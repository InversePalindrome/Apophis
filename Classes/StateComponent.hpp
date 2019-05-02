/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StateComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <pugixml.hpp>


class StateComponent
{
public:
    StateComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    State getState() const;
    void setState(State state);

private:
    State state;
};