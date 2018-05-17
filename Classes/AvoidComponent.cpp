/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"

#include <string>


AvoidComponent::AvoidComponent(const tinyxml2::XMLElement* componentNode) :
	avoidanceDistance(5.f),
	avoidanceForce(10.f)
{
	if (const auto* avoidanceDistance = componentNode->Attribute("distance"))
	{
		this->avoidanceDistance = std::stof(avoidanceDistance);
	}
	if (const auto* avoidanceForce = componentNode->Attribute("force"))
	{
		this->avoidanceForce = std::stof(avoidanceForce);
	}
}

float AvoidComponent::getAvoidanceDistance() const
{
	return avoidanceDistance;
}

void AvoidComponent::setAvoidanceDistance(float avoidanceDistance)
{
	this->avoidanceDistance = avoidanceDistance;
}

float AvoidComponent::getAvoidanceForce() const
{
	return avoidanceForce;
}

void AvoidComponent::setAvoidanceForce(float avoidanceForce)
{
	this->avoidanceForce = avoidanceForce;
}