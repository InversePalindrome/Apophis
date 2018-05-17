/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ImpulseComponent
{
public:
	explicit ImpulseComponent(const tinyxml2::XMLElement* componentNode);

	float getImpulse() const;
	void setImpulse(float impulse);

private:
	float impulse;
};