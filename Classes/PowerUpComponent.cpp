/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PowerUpComponent.cpp
InversePalindrome.com
*/


#include "PowerUpComponent.hpp"

#include <string>


PowerUpComponent::PowerUpComponent(const tinyxml2::XMLElement* componentNode) :
	effectBoost(5.f),
	effectTime(1.f)
{
	if (const auto* effectBoost = componentNode->Attribute("boost"))
	{
		this->effectBoost = std::stof(effectBoost);
	}
	if (const auto* effectTime = componentNode->Attribute("time"))
	{
		this->effectTime = std::stof(effectTime);
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

float PowerUpComponent::getEffectTime() const
{
	return effectTime;
}

void PowerUpComponent::setEffectTime(float effectTime)
{
	this->effectTime = effectTime;
}