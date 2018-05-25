/*
Copyright (c) 2018 Inverse Palindrome
Apophis- ArriveComponent.cpp
InversePalindrome.com
*/


#include "ArriveComponent.hpp"

#include <string>


ArriveComponent::ArriveComponent(const tinyxml2::XMLElement* componentNode) :
	slowRadius(5.f)
{
	if (const auto* slowRadius = componentNode->GetText())
	{
		this->slowRadius = std::stof(slowRadius);
	}
}

float ArriveComponent::getSlowRadius() const
{
	return slowRadius;
}

void ArriveComponent::setSlowRadius(float slowRadius)
{
	this->slowRadius = slowRadius;
}