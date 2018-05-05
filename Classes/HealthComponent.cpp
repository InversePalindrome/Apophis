/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - HealthComponent.cpp
InversePalindrome.com
*/


#include "HealthComponent.hpp"

#include <string>


HealthComponent::HealthComponent(const tinyxml2::XMLElement* componentNode) :
	hitpoints(0)
{
	if (const auto* hitpoints = componentNode->GetText())
	{
		this->hitpoints = std::stoi(hitpoints);
	}
}

int HealthComponent::getHitpoints() const
{
	return hitpoints;
}

void HealthComponent::setHitpoints(int hitpoints)
{
	this->hitpoints = hitpoints;
}