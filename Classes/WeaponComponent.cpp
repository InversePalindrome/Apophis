/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WeaponComponent.cpp
InversePalindrome.com
*/


#include "WeaponComponent.hpp"


WeaponComponent::WeaponComponent(const tinyxml2::XMLElement* componentNode) :
	reloadTime(1000),
	reloadStatus(true)
{
	if (const auto* projectileName = componentNode->Attribute("projectileName"))
	{
		this->projectileName = projectileName;
	}
	if (const auto* reloadTime = componentNode->Attribute("reloadTime"))
	{
		this->reloadTime = std::chrono::milliseconds(std::stoi(reloadTime));
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
