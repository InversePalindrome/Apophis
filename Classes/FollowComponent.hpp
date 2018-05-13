/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - FollowComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class FollowComponent
{
public:
	explicit FollowComponent(const tinyxml2::XMLElement* componentNode);

	float getLeaderSight() const;
	void setLeaderSight(float leaderSight);

	float getDistanceFromLeader() const;
	void setDistanceFromLeader(float distanceFromLeader);

private:
	float leaderSight;
	float distanceFromLeader;
};