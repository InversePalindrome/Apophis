/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedBoostComponent.cpp
InversePalindrome.com
*/


#include "SpeedBoostComponent.hpp"


SpeedBoostComponent::SpeedBoostComponent(const pugi::xml_node& componentNode) :
	speedBoostPercent(5.f),
	speedBoostDuration(1000)
{
	if (const auto speedBoostPercentAttribute = componentNode.attribute("boost"))
	{
		speedBoostPercent = speedBoostPercentAttribute.as_float();
	}
	if (const auto speedBoostDurationAttribute = componentNode.attribute("duration"))
	{
		speedBoostDuration = std::chrono::milliseconds(speedBoostDurationAttribute.as_int());
	}
}

float SpeedBoostComponent::getSpeedBoostPercent() const
{
	return speedBoostPercent;
}

void SpeedBoostComponent::setSpeedBoostPercent(float speedBoostPercent)
{
	this->speedBoostPercent = speedBoostPercent;
}

std::chrono::milliseconds SpeedBoostComponent::getSpeedBoostDuration() const
{
	return speedBoostDuration;
}

void SpeedBoostComponent::setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration)
{
	this->speedBoostDuration = speedBoostDuration;
}