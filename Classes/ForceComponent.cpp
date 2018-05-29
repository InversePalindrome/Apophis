/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ForceComponent.cpp
InversePalindrome.com
*/


#include "ForceComponent.hpp"

#include <string>


ForceComponent::ForceComponent(const tinyxml2::XMLElement* componentNode) :
	linearForce(10.f),
	angularForce(10.f)
{
	if (const auto* linearForce = componentNode->Attribute("linear"))
	{
		this->linearForce = std::stof(linearForce);
	}
	if (const auto* angularForce = componentNode->Attribute("angular"))
	{
		this->angularForce = std::stof(angularForce);
	}
}

float ForceComponent::getLinearForce() const
{
	return linearForce;
}

void ForceComponent::setLinearForce(float linearForce)
{
	this->linearForce = linearForce;
}

float ForceComponent::getAngularForce() const
{
	return angularForce;
}

void ForceComponent::setAngularForce(float angularForce)
{
	this->angularForce = angularForce;
}