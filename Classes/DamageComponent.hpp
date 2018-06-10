/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DamageComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class DamageComponent
{
public:
	explicit DamageComponent(const pugi::xml_node& componentNode);

	float getDamageHitpoints() const;
	void setDamageHitpoints(float hitpoints);

private:
	float damageHitpoints;
};