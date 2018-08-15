/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.cpp
InversePalindrome.com
*/


#include "ExplosionComponent.hpp"

#include <imgui.h>

#include <nfd.h>


ExplosionComponent::ExplosionComponent(const pugi::xml_node& componentNode) :
	explosionTime(1000)
{
	if (const auto explosionFilenameAttribute = componentNode.attribute("filename"))
	{
		setExplosionFilename(explosionFilenameAttribute.as_string());
	}
	if (const auto explosionTimeAttribute = componentNode.attribute("time"))
	{
		setExplosionTime(std::chrono::milliseconds(explosionTimeAttribute.as_int()));
	}
}

void ExplosionComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Explosion");

	componentNode.append_attribute("filename") = explosionFilename.c_str();
	componentNode.append_attribute("time") = explosionTime.count();
}

void ExplosionComponent::display()
{
	if (ImGui::TreeNode("Explosion"))
	{
		explosionFilename.reserve(64);

		ImGui::InputText("Filename", explosionFilename.data(), explosionFilename.length());
		ImGui::SameLine();
		if (ImGui::Button("Select"))
		{
			nfdchar_t* filename = nullptr;

			if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
			{
				setExplosionFilename(filename);
			}
		}

		if (auto explosionTimeCount = static_cast<int>(explosionTime.count()); ImGui::InputInt("Time(milliseconds)", &explosionTimeCount))
		{
			setExplosionTime(std::chrono::milliseconds(explosionTimeCount));
		}

		ImGui::TreePop();
	}
}

std::string ExplosionComponent::getExplosionFilename() const
{
	return explosionFilename;
}

void ExplosionComponent::setExplosionFilename(const std::string& explosionFilename)
{
	this->explosionFilename = explosionFilename;
}

std::chrono::milliseconds ExplosionComponent::getExplosionTime() const
{
	return explosionTime;
}
void ExplosionComponent::setExplosionTime(const std::chrono::milliseconds& explosionTime)
{
	this->explosionTime = explosionTime;
}