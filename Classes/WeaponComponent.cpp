/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WeaponComponent.cpp
InversePalindrome.com
*/


#include "WeaponComponent.hpp"

#include <imgui.h>

#include <nfd.h>


WeaponComponent::WeaponComponent() :
	reloadTime(1000),
	reloadStatus(true)
{
}

void WeaponComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto projectileNameAttribute = componentNode.attribute("projectileFilename"))
	{
		setProjectileFilename(projectileNameAttribute.as_string());
	}
	if (const auto reloadTimeAttribute = componentNode.attribute("reloadTime"))
	{
		setReloadTime(std::chrono::milliseconds(reloadTimeAttribute.as_int()));
	}
}

void WeaponComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Weapon");

	componentNode.append_attribute("projectileFilename") = getProjectileFilename().c_str();
	componentNode.append_attribute("reloadTime") = getReloadTime().count();
}

void WeaponComponent::display()
{
	if (ImGui::TreeNode("Weapon"))
	{
		projectileFilename.reserve(64);

		ImGui::InputText("Projectile Filename", projectileFilename.data(), projectileFilename.length());
		ImGui::SameLine();
		if (ImGui::Button("Select"))
		{
			nfdchar_t* filename = nullptr;

			if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
			{
				setProjectileFilename(filename);
			}
		}
		if (auto reloadTimeCount = static_cast<int>(getReloadTime().count()); ImGui::InputInt("Reload Time(Milliseconds)", &reloadTimeCount))
		{
			setReloadTime(std::chrono::milliseconds(reloadTimeCount));
		}

		ImGui::TreePop();
	}
}

std::string WeaponComponent::getProjectileFilename() const
{
	return projectileFilename;
}

void WeaponComponent::setProjectileFilename(const std::string& projectileFilename)
{
	this->projectileFilename = projectileFilename;
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
