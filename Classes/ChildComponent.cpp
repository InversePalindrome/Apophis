/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ChildComponent.cpp
InversePalindrome.com
*/


#include "ChildComponent.hpp"

#include <string>


ChildComponent::ChildComponent(const tinyxml2::XMLElement* componentNode) :
	parentID(0)
{
	if (const auto* parentID = componentNode->GetText())
	{
		this->parentID = std::stoi(parentID);
	}
}

int ChildComponent::getParentID() const
{
	return parentID;
}

void ChildComponent::setParentID(int parentID)
{
	this->parentID = parentID;
}