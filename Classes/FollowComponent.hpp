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

	float getDistanceFromLeader() const;
	void setDistanceFromLeader(float distanceFromLeader);

private:
	float distanceFromLeader;
};