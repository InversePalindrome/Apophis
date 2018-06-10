/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"


FlockComponent::FlockComponent(const pugi::xml_node& componentNode) :
	groupID(-1),
	groupRadius(25.f)
{
	if (const auto groupIDAttribute = componentNode.attribute("id"))
	{
		groupID = groupIDAttribute.as_int();
	}
	if (const auto groupRadiusAttribute = componentNode.attribute("radius"))
	{
		groupRadius = groupRadiusAttribute.as_float();
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