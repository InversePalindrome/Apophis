/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#include "SatelliteComponent.hpp"


SatelliteComponent::SatelliteComponent(const pugi::xml_node& componentNode) :
	primaryID(componentNode.text().as_int(-1))
{
}

int SatelliteComponent::getPrimaryID() const
{
	return primaryID;
}

void SatelliteComponent::setPrimaryID(int primaryID) 
{
	this->primaryID = primaryID;
}