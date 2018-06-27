/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AccelerationComponent.cpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class AccelerationComponent
{
public:
	explicit AccelerationComponent(const pugi::xml_node& componentNode);

	float getLinearAcceleration() const;
	void setLinearAcceleration(float linearAcceleration);

	float getAngularAcceleration() const;
	void setAngularAcceleration(float angularAcceleration);

private:
	float linearAcceleration;
	float angularAcceleration;
};