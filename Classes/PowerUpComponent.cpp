/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PowerUpComponent.cpp
InversePalindrome.com
*/


#include "PowerUpComponent.hpp"


PowerUpComponent::PowerUpComponent(const pugi::xml_node& componentNode) :
	effectBoost(5.f),
	effectTime(1000)
{
	if (const auto effectBoostAttribute = componentNode.attribute("boost"))
	{
		effectBoost = effectBoostAttribute.as_float();
	}
	if (const auto effectTimeAttribute = componentNode.attribute("time"))
	{
		effectTime = std::chrono::milliseconds(effectTimeAttribute.as_int());
	}
}

float PowerUpComponent::getEffectBoost() const
{
	return effectBoost;
}

void PowerUpComponent::setEffectBoost(float effectBoost)
{
	this->effectBoost = effectBoost;
}

std::chrono::milliseconds PowerUpComponent::getEffectTime() const
{
	return effectTime;
}

void PowerUpComponent::setEffectTime(std::chrono::milliseconds effectTime)
{
	this->effectTime = effectTime;
}