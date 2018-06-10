/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PowerUpComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class PowerUpComponent
{
public:
	explicit PowerUpComponent(const pugi::xml_node& componentNode);

	float getEffectBoost() const;
	void setEffectBoost(float effectBoost);

	std::chrono::milliseconds getEffectTime() const;
	void setEffectTime(std::chrono::milliseconds effectTime);

private:
	float effectBoost;
	std::chrono::milliseconds effectTime;
};