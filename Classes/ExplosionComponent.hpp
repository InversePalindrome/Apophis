/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <string>


class ExplosionComponent
{
public:
	explicit ExplosionComponent(const pugi::xml_node& componentNode);

	std::string getExplosionName() const;

	float getExplosionTime() const;
	void setExplosionTime(float explosionTime);

private:
	std::string explosionName;
	float explosionTime;
};