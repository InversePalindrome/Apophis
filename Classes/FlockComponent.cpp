/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"

#include <string>


FlockComponent::FlockComponent(const tinyxml2::XMLElement* componentNode) :
	groupID(-1),
	groupRadius(25.f)
{
	if (const auto* groupID = componentNode->Attribute("id"))
	{
		this->groupID = std::stof(groupID);
	}
	if (const auto* groupRadius = componentNode->Attribute("radius"))
	{
		this->groupRadius = std::stof(groupRadius);
	}
}

int FlockComponent::getGroupID() const
{
	return groupID;
}

void FlockComponent::setGroupID(int groupID)
{
	this->groupID = groupID;
}

float FlockComponent::getGroupRadius() const
{
	return groupRadius;
}

void FlockComponent::setGroupRadius(float groupRadius)
{
	this->groupRadius = groupRadius;
}