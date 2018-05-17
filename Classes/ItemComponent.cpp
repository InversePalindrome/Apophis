/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemComponent.cpp
InversePalindrome.com
*/


#include "ItemComponent.hpp"


ItemComponent::ItemComponent(const tinyxml2::XMLElement* componentNode) :
	item(Item::Undefined)
{
	if (const auto* item = componentNode->GetText())
	{
		this->item = Item::_from_string(item);
	}
}

Item ItemComponent::getItem() const
{
	return item;
}

void ItemComponent::setItem(Item item)
{
	this->item = item;
}