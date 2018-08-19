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
	SpeedBoostComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	float getSpeedBoostRatio() const;
	void setSpeedBoostRatio(float speedBoostRatio);

	std::chrono::milliseconds getSpeedBoostDuration() const;
	void setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration);

private:
	float speedBoostRatio;
	std::chrono::milliseconds speedBoostDuration;
};