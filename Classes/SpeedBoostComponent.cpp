/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedBoostComponent.cpp
InversePalindrome.com
*/


#include "SpeedBoostComponent.hpp"


SpeedBoostComponent::SpeedBoostComponent(const pugi::xml_node& componentNode) :
	speedBoostRatio(2.f),
	speedBoostDuration(1000)
{
	if (const auto speedBoostRatioAttribute = componentNode.attribute("ratio"))
	{
		setSpeedBoostRatio(speedBoostRatioAttribute.as_float());
	}
	if (const auto speedBoostDurationAttribute = componentNode.attribute("duration"))
	{
		setSpeedBoostDuration(std::chrono::milliseconds(speedBoostDurationAttribute.as_int()));
	}
}

float SpeedBoostComponent::getSpeedBoostRatio() const
{
	return speedBoostRatio;
}

void SpeedBoostComponent::setSpeedBoostRatio(float speedBoostRatio)
{
	this->speedBoostRatio = speedBoostRatio;
}

std::chrono::milliseconds SpeedBoostComponent::getSpeedBoostDuration() const
{
	return speedBoostDuration;
}

void SpeedBoostComponent::setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration)
{
	this->speedBoostDuration = speedBoostDuration;
}