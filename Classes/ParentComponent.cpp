/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParentComponent.cpp
InversePalindrome.com
*/


#include "ParentComponent.hpp"

#include <string>


ParentComponent::ParentComponent(const tinyxml2::XMLElement* componentNode)
{
	if (const auto* childID = componentNode->GetText())
	{
		this->childID = std::stoi(childID);
	}
}

int ParentComponent::getChildID() const
{
	return childID;
}

void ParentComponent::setChildID(int childID)
{
	this->childID = childID;
}