/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"

#include <string>


FlockComponent::FlockComponent(const tinyxml2::XMLElement* componentNode) :
	groupRadius(5.f)
{
	for (const auto* groupIDNode = componentNode->FirstChildElement("ID"); groupIDNode; groupIDNode = groupIDNode->NextSiblingElement("ID"))
	{
		groupIDs.push_back(std::stoi(groupIDNode->GetText()));
	}

	if (const auto* groupRadius = componentNode->Attribute("radius"))
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

const std::vector<int>& FlockComponent::getGroupIDs() 
{
	return groupIDs;
}