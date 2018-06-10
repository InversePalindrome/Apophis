/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Item.hpp"

#include <pugixml.hpp>


class ItemComponent
{
public:
	explicit ItemComponent(const pugi::xml_node& componentNode);

	Item getItem() const;
	void setItem(Item item);

private:
	Item item;
};