/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AccelerationComponent.cpp
InversePalindrome.com
*/



#include "AccelerationComponent.hpp"


AccelerationComponent::AccelerationComponent(const pugi::xml_node& componentNode) :
	linearAcceleration(1.f),
	angularAcceleration(1.f)
{
	if (const auto linearAccelerationAttribute = componentNode.attribute("linear"))
	{
		linearAcceleration = linearAccelerationAttribute.as_float();
	}
	if (const auto angularAccelerationAttribute = componentNode.attribute("angular"))
	{
		angularAcceleration = angularAccelerationAttribute.as_float();
	}
}

float AccelerationComponent::getLinearAcceleration() const
{
	return linearAcceleration;
}

void AccelerationComponent::setLinearAcceleration(float linearAcceleration)
{
	this->linearAcceleration = linearAcceleration;
}

float AccelerationComponent::getAngularAcceleration() const
{
	return angularAcceleration;
}

void AccelerationComponent::setAngularAcceleration(float angularAcceleration)
{
	this->angularAcceleration = angularAcceleration;
}