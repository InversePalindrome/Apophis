/*
Copyright (c) 2018 Inverse Palindrome
Apophis- ArriveComponent.cpp
InversePalindrome.com
*/


#include "ArriveComponent.hpp"

#include <string>


ArriveComponent::ArriveComponent(const tinyxml2::XMLElement* componentNode) :
	slowingRadius(5.f)
{
	if (const auto* slowingRadius = componentNode->GetText())
	{
		this->slowingRadius = std::stof(slowingRadius);
	}
}

float ArriveComponent::getSlowingRadius() const
{
	return slowingRadius;
}

void ArriveComponent::setSlowingRadius(float slowingRadius)
{
	this->slowingRadius = slowingRadius;
}