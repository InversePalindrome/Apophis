/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class SpeedComponent
{
public:
	explicit SpeedComponent(const tinyxml2::XMLElement* componentNode);

	float getMaxSpeed() const;
	void setMaxSpeed(float maxSpeed);

private:
	float maxSpeed;
};