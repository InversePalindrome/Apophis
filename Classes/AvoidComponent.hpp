/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AvoidComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class AvoidComponent
{
public:
	explicit AvoidComponent(const tinyxml2::XMLElement* componentNode);

	float getVisionDistance() const;
	void setVisionDistance(float visionDistance);

	float getAvoidanceForce() const;
	void setAvoidanceForce(float avoidanceForce);

private:
	float visionDistance;
	float avoidanceForce;
};