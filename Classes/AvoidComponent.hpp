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

	float getAvoidanceDistance() const;
	void setAvoidanceDistance(float avoidanceDistance);

	float getAvoidanceForce() const;
	void setAvoidanceForce(float avoidanceForce);

private:
	float avoidanceDistance;
	float avoidanceForce;
};