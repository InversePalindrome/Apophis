/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PowerUpComponent.cpp
InversePalindrome.com
*/


#include "PowerUpComponent.hpp"

#include <string>


PowerUpComponent::PowerUpComponent(const tinyxml2::XMLElement* componentNode) :
	effectBoost(5.f),
	effectTime(1000)
{
	if (const auto* effectBoost = componentNode->Attribute("boost"))
	{
		this->effectBoost = std::stof(effectBoost);
	}
	if (const auto* effectTime = componentNode->Attribute("time"))
	{
		this->effectTime = std::chrono::milliseconds(std::stoi(effectTime));
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