/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HealthComponent.cpp
InversePalindrome.com
*/


#include "HealthComponent.hpp"


HealthComponent::HealthComponent(const pugi::xml_node& componentNode) :
	maxHitpoints(componentNode.text().as_float(5.f)),
	currentHitpoints(maxHitpoints)
{
}

void HealthComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Health");

	componentNode.text().set(maxHitpoints);
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