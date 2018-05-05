/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"

#include <string>


AvoidComponent::AvoidComponent(const tinyxml2::XMLElement* componentNode) :
	visionDistance(5.f),
	avoidanceForce(10.f)
{
	if (const auto* visionDistance = componentNode->Attribute("distance"))
	{
		this->visionDistance = std::stof(visionDistance);
	}
	if (const auto* avoidanceForce = componentNode->Attribute("force"))
	{
		this->avoidanceForce = std::stof(avoidanceForce);
	}
}

float AvoidComponent::getVisionDistance() const
{
	return visionDistance;
}

void AvoidComponent::setVisionDistance(float visionDistance)
{
	this->visionDistance = visionDistance;
}

float AvoidComponent::getAvoidanceForce() const
{
	return avoidanceForce;
}

void AvoidComponent::setAvoidanceForce(float avoidanceForce)
{
	this->avoidanceForce = avoidanceForce;
}