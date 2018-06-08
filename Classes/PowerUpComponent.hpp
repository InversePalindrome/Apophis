/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PowerUpComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <chrono>


class PowerUpComponent
{
public:
	explicit PowerUpComponent(const tinyxml2::XMLElement* componentNode);

	float getEffectBoost() const;
	void setEffectBoost(float effectBoost);

	std::chrono::milliseconds getEffectTime() const;
	void setEffectTime(std::chrono::milliseconds effectTime);

private:
	float effectBoost;
	std::chrono::milliseconds effectTime;
};