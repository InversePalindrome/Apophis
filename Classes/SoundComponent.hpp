/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>
#include <unordered_map>


class SoundComponent
{
public:
	explicit SoundComponent(const tinyxml2::XMLElement* componentNode);

	std::string getSound(const std::string& action) const;

	bool hasSound(const std::string& action) const;

private:
	std::unordered_map<std::string, std::string> sounds;
};