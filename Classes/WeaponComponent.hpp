/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WeaponComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class WeaponComponent
{
public:
    WeaponComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	std::string getProjectileFilename() const;
	void setProjectileFilename(const std::string& projectileFilename);

	std::chrono::milliseconds getReloadTime() const;
	void setReloadTime(std::chrono::milliseconds reloadTime);

	bool isReloaded() const;
	void setReloadStatus(bool reloadStatus);

private:
	std::string projectileFilename;

	std::chrono::milliseconds reloadTime;
	bool reloadStatus;
};