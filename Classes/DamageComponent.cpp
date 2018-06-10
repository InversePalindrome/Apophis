/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DamageComponent.cpp
InversePalindrome.com
*/


#include "DamageComponent.hpp"


DamageComponent::DamageComponent(const pugi::xml_node& componentNode) :
	damageHitpoints(componentNode.text().as_float(1.f))
{
}

float DamageComponent::getDamageHitpoints() const
{
	return damageHitpoints;
}

void DamageComponent::setDamageHitpoints(float hitpoints)
{
	this->damageHitpoints = hitpoints;
}