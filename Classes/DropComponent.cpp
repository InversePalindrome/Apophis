/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - DropComponent.cpp
InversePalindrome.com
*/


#include "DropComponent.hpp"


DropComponent::DropComponent(const tinyxml2::XMLElement* componentNode) :
	totalRate(0.f)
{
	for (const auto* lootNode = componentNode->FirstChildElement("Loot"); lootNode; lootNode = lootNode->NextSiblingElement("Loot"))
	{
		const auto* name = lootNode->Attribute("name");
		const auto* rate = lootNode->Attribute("chance");

		if (name && rate)
		{
			totalRate += std::stof(rate);

			dropChances.insert({ totalRate, name });
		}
	}
}

float DropComponent::getTotalRate() const
{
	return totalRate;
}

const std::map<float, std::string>& DropComponent::getDropChances() const
{
	return dropChances;
}

void DropComponent::addDropChance(const std::string& name, float chance)
{
	totalRate += chance;

	dropChances.insert({ totalRate, name });
}