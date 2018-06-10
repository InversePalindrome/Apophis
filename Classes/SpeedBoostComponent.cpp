/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedBoostComponent.cpp
InversePalindrome.com
*/


#include "SpeedBoostComponent.hpp"


SpeedBoostComponent::SpeedBoostComponent(const pugi::xml_node& componentNode) :
	speedBoost(5.f),
	speedBoostDuration(1000)
{
	if (const auto speedBoostAttribute = componentNode.attribute("boost"))
	{
		speedBoost = speedBoostAttribute.as_float();
	}
	if (const auto speedBoostDurationAttribute = componentNode.attribute("duration"))
	{
		speedBoostDuration = std::chrono::milliseconds(speedBoostDurationAttribute.as_int());
	}
}

float SpeedBoostComponent::getSpeedBoost() const
{
	return speedBoost;
}

void SpeedBoostComponent::setSpeedBoost(float speedBoost)
{
	this->speedBoost = speedBoost;
}

std::chrono::milliseconds SpeedBoostComponent::getSpeedBoostDuration() const
{
	return speedBoostDuration;
}

void SpeedBoostComponent::setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration)
{
	this->speedBoostDuration = speedBoostDuration;
}