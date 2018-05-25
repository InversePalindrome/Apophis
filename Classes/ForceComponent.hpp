/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ForceComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ForceComponent
{
public:
	explicit ForceComponent(const tinyxml2::XMLElement* componentNode);

	float getLinearForce() const;
	void setLinearForce(float linearForce);

	float getRotationalForce() const;
	void setRotationalForce(float rotationalForce);

private:
	float linearForce;
	float rotationalForce;
};