/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FollowComponent.cpp
InversePalindrome.com
*/


#include "FollowComponent.hpp"


FollowComponent::FollowComponent(const pugi::xml_node& componentNode) :
	distanceFromLeader(componentNode.text().as_float(5.f))
{
}

void FollowComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Follow");

	componentNode.text().set(distanceFromLeader);
}

float FollowComponent::getDistanceFromLeader() const
{
	return distanceFromLeader;
}

void FollowComponent::setDistanceFromLeader(float distanceFromLeader)
{
	this->distanceFromLeader = distanceFromLeader;
}