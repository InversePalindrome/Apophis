/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class SpeedComponent
{
public:
	explicit SpeedComponent(const pugi::xml_node& componentNode);

	float getMaxLinearSpeed() const;
	void setMaxLinearSpeed(float maxLinearSpeed);

	float getMaxAngularSpeed() const;
	void setMaxAngularSpeed(float maxAngularSpeed);

private:
	float maxLinearSpeed;
	float maxAngularSpeed;
};