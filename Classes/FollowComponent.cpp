/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - FollowComponent.cpp
InversePalindrome.com
*/


#include "FollowComponent.hpp"

#include <string>


FollowComponent::FollowComponent(const tinyxml2::XMLElement* componentNode) :
	leaderSight(2.f),
	distanceFromLeader(5.f)
{
	if (const auto* leaderSight = componentNode->Attribute("leaderSight"))
	{
		this->leaderSight = std::stof(leaderSight);
	}
	if (const auto* distanceFromLeader = componentNode->Attribute("distance"))
	{
		this->distanceFromLeader = std::stof(distanceFromLeader);
	}
}

float FollowComponent::getLeaderSight() const
{
	return leaderSight;
}

void FollowComponent::setLeaderSight(float leaderSight)
{
	this->leaderSight = leaderSight;
}

float FollowComponent::getDistanceFromLeader() const
{
	return distanceFromLeader;
}

void FollowComponent::setDistanceFromLeader(float distanceFromLeader)
{
	this->distanceFromLeader = distanceFromLeader;
}