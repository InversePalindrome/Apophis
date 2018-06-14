/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RegenBoostComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class RegenBoostComponent
{
public:
	explicit RegenBoostComponent(const pugi::xml_node& componentNode);

	float getHitpointBoost() const;
	void setHitpointBoost(float hitpointBoost);

	std::chrono::milliseconds getRegenRate() const;
	void setRegenRate(const std::chrono::milliseconds& regenRate);

	std::chrono::milliseconds getRegenDuration() const;
	void setRegenDuration(const std::chrono::milliseconds& regenDuration);

private:
	float hitpointBoost;
	std::chrono::milliseconds regenRate;
	std::chrono::milliseconds regenDuration;
};