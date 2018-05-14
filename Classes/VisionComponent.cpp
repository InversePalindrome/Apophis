/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - VisionComponent.cpp
InversePalindrome.com
*/


#include "VisionComponent.hpp"

#include <string>


VisionComponent::VisionComponent(const tinyxml2::XMLElement* componentNode) :
	visionDistance(5.f)
{
	if (const auto* visionDistance = componentNode->GetText())
	{
		this->visionDistance = std::stof(visionDistance);
	}
}

float VisionComponent::getVisionDistance() const
{
	return visionDistance;
}

void VisionComponent::setVisionDistance(float visionDistance)
{
	this->visionDistance = visionDistance;
}