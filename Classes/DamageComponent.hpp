/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DamageComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class DamageComponent
{
public:
	explicit DamageComponent(const tinyxml2::XMLElement* componentNode);

	float getDamageHitpoints() const;
	void setDamageHitpoints(float hitpoints);

private:
	float damageHitpoints;
};