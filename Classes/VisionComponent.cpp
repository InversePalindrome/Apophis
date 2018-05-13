/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - VisionComponent.cpp
InversePalindrome.com
*/


#include "VisionComponent.hpp"

#include <string>


VisionComponent::VisionComponent(const tinyxml2::XMLElement* componentNode) :
	visionRadius(5.f)
{
	if (const auto* visionRadius = componentNode->GetText())
	{
		this->visionRadius = std::stof(visionRadius);
	}
}

float VisionComponent::getVisionRadius() const
{
	return visionRadius;
}

void VisionComponent::setVisionRadius(float visionRadius)
{
	this->visionRadius = visionRadius;
}