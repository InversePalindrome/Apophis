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

	float getSpeedBoostRatio() const;
	void setSpeedBoostRatio(float speedBoostRatio);

	std::chrono::milliseconds getSpeedBoostDuration() const;
	void setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration);

private:
	float speedBoostRatio;
	std::chrono::milliseconds speedBoostDuration;
};