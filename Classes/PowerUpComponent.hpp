/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PowerUpComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "PowerUpType.hpp"

#include <tinyxml2/tinyxml2.h>


class PowerUpComponent
{
public:
	explicit PowerUpComponent(const tinyxml2::XMLElement* componentNode);

	PowerUpType getPowerUpType() const;
	void setPowerUpType(PowerUpType powerUp);

	float getEffectBoost() const;
	void setEffectBoost(float effectBoost);

	float getEffectTime() const;
	void setEffectTime(float effectTime);

private:
	PowerUpType powerUpType;

	float effectBoost;
	float effectTime;
};