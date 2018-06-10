/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HealthComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class HealthComponent
{
public:
	explicit HealthComponent(const pugi::xml_node& componentNode);
	
	float getMaxHitpoints() const;
	void setMaxHitpoints(float maxHitpoints);

	float getCurrentHitpoints() const;
	void setCurrentHitpoints(float currentHitpoints);

private:
	float maxHitpoints;
	float currentHitpoints;
};