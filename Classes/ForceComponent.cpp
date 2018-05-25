/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ForceComponent.cpp
InversePalindrome.com
*/


#include "ForceComponent.hpp"

#include <string>


ForceComponent::ForceComponent(const tinyxml2::XMLElement* componentNode) :
	linearForce(10.f),
	rotationalForce(1.f)
{
	if (const auto* linearForce = componentNode->Attribute("linear"))
	{
		this->linearForce = std::stof(linearForce);
	}
	if (const auto* rotationalForce = componentNode->Attribute("rotational"))
	{
		this->rotationalForce = std::stof(rotationalForce);
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

float ForceComponent::getRotationalForce() const
{
	return rotationalForce;
}

void ForceComponent::setRotationalForce(float rotationalForce)
{
	this->rotationalForce = rotationalForce;
}