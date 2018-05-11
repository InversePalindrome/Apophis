/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - HealthComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class HealthComponent
{
public:
	explicit HealthComponent(const tinyxml2::XMLElement* componentNode);
	
	float getMaxHitpoints() const;
	void setMaxHitpoints(float maxHitpoints);

	float getCurrentHitpoints() const;
	void setCurrentHitpoints(float currentHitpoints);

private:
	float maxHitpoints;
	float currentHitpoints;
};