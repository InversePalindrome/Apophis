/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.cpp
InversePalindrome.com
*/


#include "DropComponent.hpp"


DropComponent::DropComponent(const tinyxml2::XMLElement* componentNode) :
	randomEngine(std::random_device()())
{
	for (const auto* itemNode = componentNode->FirstChildElement(); itemNode; itemNode = itemNode->NextSiblingElement())
	{
		items.push_back(itemNode->Value());
		weights.push_back(std::stoi(itemNode->GetText()));
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

void DropComponent::removeItem(const std::string& name)
{
	auto position = std::find(std::cbegin(items), std::cend(items), name) - std::begin(items);

	items.erase(std::cbegin(items) + position);
	weights.erase(std::cbegin(weights) + position);
}