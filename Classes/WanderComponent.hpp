/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - WanderComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class WanderComponent
{
public:
	explicit WanderComponent(const tinyxml2::XMLElement* componentNode);

	float getWanderDistance() const;
	void setWanderDistance(float wanderDistance);

	float getWanderRadius() const;
	void setWanderRadius(float wanderRadius);

	float getWanderRate() const;
	void setWanderRate(float wanderRate);

	float getWanderAngle() const;
	float& getWanderAngle();

private:
	float wanderDistance;
	float wanderRadius;
	float wanderRate;
	float wanderAngle;
};