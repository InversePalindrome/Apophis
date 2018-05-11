/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PowerUpComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class PowerUpComponent
{
public:
	explicit PowerUpComponent(const tinyxml2::XMLElement* componentNode);

	float getEffectBoost() const;
	void setEffectBoost(float effectBoost);

	float getEffectTime() const;
	void setEffectTime(float effectTime);

private:
	float effectBoost;
	float effectTime;
};