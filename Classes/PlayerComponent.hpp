/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class PlayerComponent
{
public:
	void save(pugi::xml_node& componentNode) const;
};