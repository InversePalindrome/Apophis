/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.cpp
InversePalindrome.com
*/


#include "ImpulseComponent.hpp"

#include <string>


ImpulseComponent::ImpulseComponent(const tinyxml2::XMLElement* componentNode) :
	impulse(10.f)
{
	if (const auto* impulse = componentNode->GetText())
	{
		this->impulse = std::stof(impulse);
	}
}

float ImpulseComponent::getImpulse() const
{
	return impulse;
}

void ImpulseComponent::setImpulse(float impulse)
{
	this->impulse = impulse;
}