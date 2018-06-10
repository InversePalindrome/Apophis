/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemComponent.cpp
InversePalindrome.com
*/


#include "ItemComponent.hpp"


ItemComponent::ItemComponent(const pugi::xml_node& componentNode) :
	item(Item::_from_string(componentNode.text().as_string()))
{
}

Item ItemComponent::getItem() const
{
	return item;
}

void ItemComponent::setItem(Item item)
{
	this->item = item;
}