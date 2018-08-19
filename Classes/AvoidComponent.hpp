/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class AvoidComponent
{
public:
	AvoidComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	float getAvoidanceAheadDistance() const;
	void setAvoidanceAheadDistance(float avoidanceAheadDistance);

	float getAvoidanceForce() const;
	void setAvoidanceForce(float avoidanceForce);

private:
	float avoidanceAheadDistance;
	float avoidanceForce;
};