/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#include "SatelliteComponent.hpp"


SatelliteComponent::SatelliteComponent(const pugi::xml_node& componentNode) :
	primaryID(-1),
	orbitDirection(1)
{
	if (const auto primaryIDAttribute = componentNode.attribute("primaryID"))
	{
		primaryID = primaryIDAttribute.as_int();
	}
	if (const auto orbitDirectionAttribute = componentNode.attribute("direction"))
	{
		orbitDirection = orbitDirectionAttribute.as_int();
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

std::int8_t SatelliteComponent::getOrbitDirection() const
{
	return orbitDirection;
}

void SatelliteComponent::setOrbitDirection(std::int8_t orbitDirection)
{
	this->orbitDirection = orbitDirection;
}