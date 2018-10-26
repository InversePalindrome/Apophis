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
	FollowComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	int getLeaderID() const;
	void setLeaderID(int leaderID);

	float getDistanceFromLeader() const;
	void setDistanceFromLeader(float distanceFromLeader);

private:
	int leaderID;
	float distanceFromLeader;
};