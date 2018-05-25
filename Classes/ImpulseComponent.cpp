/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.cpp
InversePalindrome.com
*/


#include "ImpulseComponent.hpp"

#include <string>


ImpulseComponent::ImpulseComponent(const tinyxml2::XMLElement* componentNode) :
	linearImpulse(10.f),
	angularImpulse(10.f)
{
	if (const auto* linearImpulse = componentNode->Attribute("linear"))
	{
		this->linearImpulse = std::stof(linearImpulse);
	}
	if (const auto* angularImpulse = componentNode->Attribute("angular"))
	{
		this->angularImpulse = std::stof(angularImpulse);
	}
}

float ImpulseComponent::getLinearImpulse() const
{
	return linearImpulse;
}

void ImpulseComponent::setLinearImpulse(float linearImpulse)
{
	this->linearImpulse = linearImpulse;
}

float ImpulseComponent::getAngularImpulse() const
{
	return angularImpulse;
}

void ImpulseComponent::setAngularImpulse(float angularImpulse)
{
	this->angularImpulse = angularImpulse;
}