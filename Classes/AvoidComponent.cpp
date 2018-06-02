/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"

#include <string>


AvoidComponent::AvoidComponent(const tinyxml2::XMLElement* componentNode) :
	avoidanceAheadDistance(10.f),
	avoidanceForce(50.f)
{
	if (const auto* avoidanceAheadDistance = componentNode->Attribute("distance"))
	{
		this->avoidanceAheadDistance = std::stof(avoidanceAheadDistance);
	}
	if (const auto* avoidanceForce = componentNode->Attribute("force"))
	{
		this->avoidanceForce = std::stof(avoidanceForce);
	}
}

float AvoidComponent::getAvoidanceAheadDistance() const
{
	return avoidanceAheadDistance;
}

void AvoidComponent::setAvoidanceAheadDistance(float avoidanceAheadDistance)
{
	this->avoidanceAheadDistance = avoidanceAheadDistance;
}

float AvoidComponent::getAvoidanceForce() const
{
	return avoidanceForce;
}

void AvoidComponent::setAvoidanceForce(float avoidanceForce)
{
	this->avoidanceForce = avoidanceForce;
}