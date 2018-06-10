/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedBoostComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class SpeedBoostComponent
{
public:
	explicit SpeedBoostComponent(const pugi::xml_node& componentNode);

	float getSpeedBoost() const;
	void setSpeedBoost(float speedBoost);

	std::chrono::milliseconds getSpeedBoostDuration() const;
	void setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration);

private:
	float speedBoost;
	std::chrono::milliseconds speedBoostDuration;
};