/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ItemComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Item.hpp"

#include <tinyxml2/tinyxml2.h>


class ItemComponent
{
public:
	explicit ItemComponent(const tinyxml2::XMLElement* componentNode);

	Item getItem() const;
	void setItem(Item item);

private:
	Item item;
};