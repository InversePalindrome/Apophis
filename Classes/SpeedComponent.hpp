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

	float getMaxLinearSpeed() const;
	void setMaxLinearSpeed(float maxLinearSpeed);

	float getMaxAngularSpeed() const;
	void setMaxAngularSpeed(float maxAngularSpeed);

private:
	float maxLinearSpeed;
	float maxAngularSpeed;
};