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
    HealthComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();
	
	float getMaxHitpoints() const;
	void setMaxHitpoints(float maxHitpoints);

	float getCurrentHitpoints() const;
	void setCurrentHitpoints(float currentHitpoints);

private:
	float maxHitpoints;
	float currentHitpoints;
};