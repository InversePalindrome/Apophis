/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RegenBoostComponent.cpp
InversePalindrome.com
*/


#include "RegenBoostComponent.hpp"


RegenBoostComponent::RegenBoostComponent(const pugi::xml_node& componentNode)
{
	if (const auto hitpointBoostAttribute = componentNode.attribute("boost"))
	{
		hitpointBoost = hitpointBoostAttribute.as_float();
	}
	if (const auto regenRateAttribute = componentNode.attribute("rate"))
	{
		regenRate = std::chrono::milliseconds(regenRateAttribute.as_int());
	}
	if (const auto regenPeriodAttribute = componentNode.attribute("period"))
	{
		regenPeriod = std::chrono::milliseconds(regenPeriodAttribute.as_int());
	}
}

float RegenBoostComponent::getHitpointBoost() const
{
	return hitpointBoost;
}

void RegenBoostComponent::setHitpointBoost(float hitpointBoost)
{
	this->hitpointBoost = hitpointBoost;
}

std::chrono::milliseconds RegenBoostComponent::getRegenRate() const
{
	return regenRate;
}

void RegenBoostComponent::setRegenRate(const std::chrono::milliseconds& regenRate)
{
	this->regenRate = regenRate;
}

std::chrono::milliseconds RegenBoostComponent::getRegenPeriod() const
{
	return regenPeriod;
}

void RegenBoostComponent::setRegenPeriod(const std::chrono::milliseconds& regenPeriod)
{
	this->regenPeriod = regenPeriod;
}