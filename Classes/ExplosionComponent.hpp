/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ExplosionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>


class ExplosionComponent
{
public:
	explicit ExplosionComponent(const tinyxml2::XMLElement* componentNode);

	std::string getExplosionName() const;

	float getExplosionTime() const;
	void setExplosionTime(float explosionTime);

private:
	std::string explosionName;
	float explosionTime;
};