/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - DamageComponent.cpp
InversePalindrome.com
*/


#include "DamageComponent.hpp"

#include <string>


DamageComponent::DamageComponent(const tinyxml2::XMLElement* componentNode) :
	damageHitpoints(1.f)
{
	if (const auto* damageHitpoints = componentNode->GetText())
	{
		this->damageHitpoints = std::stof(damageHitpoints);
	}
}

float DamageComponent::getDamageHitpoints() const
{
	return damageHitpoints;
}

void DamageComponent::setDamageHitpoints(float hitpoints)
{
	this->damageHitpoints = hitpoints;
}