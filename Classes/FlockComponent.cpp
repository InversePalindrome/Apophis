/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"

#include <string>


FlockComponent::FlockComponent(const tinyxml2::XMLElement* componentNode) :
	groupRadius(5.f)
{
	if (const auto* groupRadius = componentNode->GetText())
	{
		this->groupRadius = std::stof(groupRadius);
	}
}

float FlockComponent::getGroupRadius() const
{
	return groupRadius;
}

void FlockComponent::setGroupRadius(float groupRadius)
{
	this->groupRadius = groupRadius;
}