/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - DamageComponent.cpp
InversePalindrome.com
*/


#include "DamageComponent.hpp"

#include <string>


DamageComponent::DamageComponent(const tinyxml2::XMLElement* componentNode) :
	hitpoints(0)
{
	if (const auto* hitpoints = componentNode->GetText())
	{
		this->hitpoints = std::stoi(hitpoints);
	}
}

int DamageComponent::getHitpoints() const
{
	return hitpoints;
}

void DamageComponent::setHitpoints(int hitpoints)
{
	this->hitpoints = hitpoints;
}