/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"


AvoidComponent::AvoidComponent(const pugi::xml_node& componentNode) :
	avoidanceAheadDistance(10.f),
	avoidanceForce(50.f)
{
	if (const auto distanceAttribute = componentNode.attribute("distance"))
	{
		setAvoidanceAheadDistance(distanceAttribute.as_float());
	}
	if (const auto avoidanceForceAttribute = componentNode.attribute("force"))
	{
	    setAvoidanceForce(avoidanceForceAttribute.as_float());
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