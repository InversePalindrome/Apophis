/*
Copyright (c) 2018 Inverse Palindrome
Apophis - VisionComponent.cpp
InversePalindrome.com
*/


#include "VisionComponent.hpp"


VisionComponent::VisionComponent(const pugi::xml_node& componentNode) :
	visionDistance(componentNode.text().as_float(10.f))
{
}

float VisionComponent::getVisionDistance() const
{
	return visionDistance;
}

void VisionComponent::setVisionDistance(float visionDistance)
{
	this->visionDistance = visionDistance;
}