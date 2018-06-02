/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class AvoidComponent
{
public:
	explicit AvoidComponent(const tinyxml2::XMLElement* componentNode);

	float getAvoidanceAheadDistance() const;
	void setAvoidanceAheadDistance(float avoidanceAheadDistance);

	float getAvoidanceForce() const;
	void setAvoidanceForce(float avoidanceForce);

private:
	float avoidanceAheadDistance;
	float avoidanceForce;
};