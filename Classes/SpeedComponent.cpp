/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.cpp
InversePalindrome.com
*/


#include "SpeedComponent.hpp"

#include <string>


SpeedComponent::SpeedComponent(const tinyxml2::XMLElement* componentNode) :
	maxSpeed(10.f)
{
	if (const auto* maxSpeed = componentNode->GetText())
	{
		this->maxSpeed = std::stof(maxSpeed);
	}
}

float SpeedComponent::getMaxSpeed() const
{
	return maxSpeed;
}

void SpeedComponent::setMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}