/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#include "SatelliteComponent.hpp"

#include <string>


SatelliteComponent::SatelliteComponent(const tinyxml2::XMLElement* componentNode) :
	primaryID(-1)
{
	if (const auto* primaryID = componentNode->GetText())
	{
		this->primaryID = std::stoi(primaryID);
	}
}

int SatelliteComponent::getPrimaryID() const
{
	return primaryID;
}

void SatelliteComponent::setPrimaryID(int primaryID) 
{
	this->primaryID = primaryID;
}