/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.cpp
InversePalindrome.com
*/


#include "DropComponent.hpp"


DropComponent::DropComponent(const pugi::xml_node& componentNode) 
{
	for (const auto itemNode : componentNode.children())
	{
		addItem(itemNode.name(), itemNode.text().as_int());
	}
}

const std::vector<std::string>& DropComponent::getItems() const
{
	return items;
}

const std::vector<int>& DropComponent::getWeights() const
{
	return weights;
}

void DropComponent::addItem(const std::string& item, int weight)
{
	items.push_back(item);
	weights.push_back(weight);
}

void DropComponent::removeItem(const std::string& item)
{
	auto index = std::find(std::cbegin(items), std::cend(items), item) - std::cbegin(items);

	items.erase(std::cbegin(items) + index);
	weights.erase(std::cbegin(weights) + index);
}