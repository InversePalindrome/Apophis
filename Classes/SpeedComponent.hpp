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

	void save(pugi::xml_node& componentNode) const;

	float getMaxLinearSpeed() const;
	void setMaxLinearSpeed(float maxLinearSpeed);

	float getMaxAngularSpeed() const;
	void setMaxAngularSpeed(float maxAngularSpeed);

private:
	float maxLinearSpeed;
	float maxAngularSpeed;
};