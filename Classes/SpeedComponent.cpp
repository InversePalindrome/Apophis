/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.cpp
InversePalindrome.com
*/


#include "SpeedComponent.hpp"

#include <string>


SpeedComponent::SpeedComponent(const tinyxml2::XMLElement* componentNode) :
	maxLinearSpeed(10.f),
	maxAngularSpeed(10.f)
{
	if (const auto* maxLinearSpeed = componentNode->Attribute("linear"))
	{
		this->maxLinearSpeed = std::stof(maxLinearSpeed);
	}
	if (const auto* maxAngularSpeed = componentNode->Attribute("angular"))
	{
		this->maxAngularSpeed = std::stof(maxAngularSpeed);
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