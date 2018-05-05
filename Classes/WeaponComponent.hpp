/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - WeaponComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>


class WeaponComponent
{
public:
	explicit WeaponComponent(const tinyxml2::XMLElement* componentNode);

	std::string getProjectileName() const;
	void setProjectileName(const std::string& projectileName);

	float getReloadTime() const;
	void setReloadTime(float reloadTime);

	bool isReloaded() const;
	void setReloadStatus(bool reloadStatus);

private:
	std::string projectileName;
	float reloadTime;
	bool reloadStatus;
};