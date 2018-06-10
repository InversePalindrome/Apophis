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
	explicit AvoidComponent(const pugi::xml_node& componentNode);

	float getAvoidanceAheadDistance() const;
	void setAvoidanceAheadDistance(float avoidanceAheadDistance);

	float getAvoidanceForce() const;
	void setAvoidanceForce(float avoidanceForce);

private:
	float avoidanceAheadDistance;
	float avoidanceForce;
};