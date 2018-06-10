/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FollowComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class FollowComponent
{
public:
	explicit FollowComponent(const pugi::xml_node& componentNode);

	float getDistanceFromLeader() const;
	void setDistanceFromLeader(float distanceFromLeader);

private:
	float distanceFromLeader;
};