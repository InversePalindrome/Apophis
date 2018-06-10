/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.cpp
InversePalindrome.com
*/


#include "SpeedComponent.hpp"


SpeedComponent::SpeedComponent(const pugi::xml_node& componentNode) :
	maxLinearSpeed(10.f),
	maxAngularSpeed(10.f)
{
	if (const auto maxLinearSpeedAttribute = componentNode.attribute("linear"))
	{
		maxLinearSpeed = maxLinearSpeedAttribute.as_float();
	}
	if (const auto maxAngularSpeedAttribute = componentNode.attribute("angular"))
	{
		maxAngularSpeed = maxAngularSpeedAttribute.as_float();
	}
}

float SpeedComponent::getMaxLinearSpeed() const
{
	return maxLinearSpeed;
}

void SpeedComponent::setMaxLinearSpeed(float maxLinearSpeed)
{
	this->maxLinearSpeed = maxLinearSpeed;
}

float SpeedComponent::getMaxAngularSpeed() const
{
	return maxAngularSpeed;
}

void SpeedComponent::setMaxAngularSpeed(float maxAngularSpeed)
{
	this->maxAngularSpeed = maxAngularSpeed;
}