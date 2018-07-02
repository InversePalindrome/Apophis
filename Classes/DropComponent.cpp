/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.cpp
InversePalindrome.com
*/


#include "DropComponent.hpp"


DropComponent::DropComponent(const pugi::xml_node& componentNode) :
	randomEngine(std::random_device()())
{
	for (const auto itemNode : componentNode.children())
	{
		items.push_back(itemNode.name());
		weights.push_back(itemNode.text().as_int());
	}
}

std::string DropComponent::getItem()
{
	std::discrete_distribution<> distribution(std::cbegin(weights), std::cend(weights));

	return items.at(distribution(randomEngine));
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