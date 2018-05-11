/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - DropComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <map>
#include <string>


class DropComponent
{
public:
	explicit DropComponent(const tinyxml2::XMLElement* componentNode);

	float getTotalRate() const;
	const std::map<float, std::string>& getDropChances() const;
	
	void addDropChance(const std::string& name, float chance);

private:
	float totalRate;

	std::map<float, std::string> dropChances;
};