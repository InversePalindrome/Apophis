/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WeaponComponent.cpp
InversePalindrome.com
*/


#include "WeaponComponent.hpp"


WeaponComponent::WeaponComponent(const pugi::xml_node& componentNode) :
	reloadTime(1000),
	reloadStatus(true)
{
	if (const auto projectileNameAttribute = componentNode.attribute("projectileName"))
	{
		setProjectileName(projectileNameAttribute.as_string());
	}
	if (const auto reloadTimeAttribute = componentNode.attribute("reloadTime"))
	{
		setReloadTime(std::chrono::milliseconds(reloadTimeAttribute.as_int()));
	}
}

std::string WeaponComponent::getProjectileName() const
{
	return projectileName;
}

void WeaponComponent::setProjectileName(const std::string& projectileName)
{
	this->projectileName = projectileName;
}

std::chrono::milliseconds WeaponComponent::getReloadTime() const
{
	return reloadTime;
}

void WeaponComponent::setReloadTime(std::chrono::milliseconds reloadTime)
{
	this->reloadTime = reloadTime;
}

bool WeaponComponent::isReloaded() const
{
	return reloadStatus;
}

void WeaponComponent::setReloadStatus(bool reloadStatus)
{
	this->reloadStatus = reloadStatus;
}
