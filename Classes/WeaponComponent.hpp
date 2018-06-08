/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WeaponComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>
#include <chrono>


class WeaponComponent
{
public:
	explicit WeaponComponent(const tinyxml2::XMLElement* componentNode);

	std::string getProjectileName() const;
	void setProjectileName(const std::string& projectileName);

	std::chrono::milliseconds getReloadTime() const;
	void setReloadTime(std::chrono::milliseconds reloadTime);

	bool isReloaded() const;
	void setReloadStatus(bool reloadStatus);

private:
	std::string projectileName;
	std::chrono::milliseconds reloadTime;
	bool reloadStatus;
};