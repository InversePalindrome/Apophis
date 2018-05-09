/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PowerUpComponent.cpp
InversePalindrome.com
*/


#include "PowerUpComponent.hpp"

#include <string>


PowerUpComponent::PowerUpComponent(const tinyxml2::XMLElement* componentNode) :
	powerUpType(PowerUpType::Undefined),
	effectBoost(0.f),
	effectTime(1.f)
{
	if (const auto* powerUpType = componentNode->Attribute("type"))
	{
		this->powerUpType = PowerUpType::_from_string(powerUpType);
	}
	if (const auto* effectBoost = componentNode->Attribute("boost"))
	{
		this->effectBoost = std::stof(effectBoost);
	}
	if (const auto* effectTime = componentNode->Attribute("time"))
	{
		this->effectTime = std::stof(effectTime);
	}
}

PowerUpType PowerUpComponent::getPowerUpType() const
{
	return powerUpType;
}

void PowerUpComponent::setPowerUpType(PowerUpType powerUpType)
{
	this->powerUpType = powerUpType;
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