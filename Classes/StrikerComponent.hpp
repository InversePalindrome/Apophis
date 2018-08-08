/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class StrikerComponent
{
public:
	void save(pugi::xml_node& componentNode) const;

	void display();
};