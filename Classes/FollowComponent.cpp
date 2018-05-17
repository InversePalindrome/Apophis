/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FollowComponent.cpp
InversePalindrome.com
*/


#include "FollowComponent.hpp"

#include <string>


FollowComponent::FollowComponent(const tinyxml2::XMLElement* componentNode) :
	distanceFromLeader(5.f)
{
	if (const auto* distanceFromLeader = componentNode->GetText())
	{
		this->distanceFromLeader = std::stof(distanceFromLeader);
	}
}

float FollowComponent::getDistanceFromLeader() const
{
	return distanceFromLeader;
}

void FollowComponent::setDistanceFromLeader(float distanceFromLeader)
{
	this->distanceFromLeader = distanceFromLeader;
}