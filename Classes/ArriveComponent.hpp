/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ArriveComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ArriveComponent
{
public:
	explicit ArriveComponent(const tinyxml2::XMLElement* componentNode);

	float getSlowRadius() const;
	void setSlowRadius(float slowRadius);

private:
	float slowRadius;
};