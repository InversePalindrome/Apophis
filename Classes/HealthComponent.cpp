/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HealthComponent.cpp
InversePalindrome.com
*/


#include "HealthComponent.hpp"

#include <string>


HealthComponent::HealthComponent(const tinyxml2::XMLElement* componentNode) :
	maxHitpoints(5.f)
{
	if (const auto* maxHitpoints = componentNode->GetText())
	{
		this->maxHitpoints = std::stof(maxHitpoints);
	}
	
	currentHitpoints = maxHitpoints;
}

float HealthComponent::getMaxHitpoints() const
{
	return maxHitpoints;
}

void HealthComponent::setMaxHitpoints(float maxHitpoints)
{
	this->maxHitpoints = maxHitpoints;
}

float HealthComponent::getCurrentHitpoints() const
{
	return currentHitpoints;
}

void HealthComponent::setCurrentHitpoints(float currentHitpoints)
{
	this->currentHitpoints = currentHitpoints;
}