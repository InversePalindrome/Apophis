/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.cpp
InversePalindrome.com
*/


#include "ExplosionComponent.hpp"

#include <imgui.h>


ExplosionComponent::ExplosionComponent(const pugi::xml_node& componentNode) :
	explosionTime(1000)
{
	if (const auto explosionNameAttribute = componentNode.attribute("name"))
	{
		setExplosionName(explosionNameAttribute.as_string());
	}
	if (const auto explosionTimeAttribute = componentNode.attribute("time"))
	{
		setExplosionTime(std::chrono::milliseconds(explosionTimeAttribute.as_int()));
	}
}

void ExplosionComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Explosion");

	componentNode.append_attribute("name") = explosionName.c_str();
	componentNode.append_attribute("time") = explosionTime.count();
}

void ExplosionComponent::display()
{
	if (ImGui::TreeNode("Explosion"))
	{
		explosionName.resize(64);
		ImGui::InputText("Name", explosionName.data(), explosionName.length());

		if (auto explosionTimeCount = static_cast<int>(explosionTime.count()); ImGui::InputInt("Time(milliseconds)", &explosionTimeCount))
		{
			setExplosionTime(std::chrono::milliseconds(explosionTimeCount));
		}

		ImGui::TreePop();
	}
}

std::string ExplosionComponent::getExplosionName() const
{
	return explosionName;
}

void ExplosionComponent::setExplosionName(const std::string& explosionName)
{
	this->explosionName = explosionName;
}

std::chrono::milliseconds ExplosionComponent::getExplosionTime() const
{
	return explosionTime;
}
void ExplosionComponent::setExplosionTime(const std::chrono::milliseconds& explosionTime)
{
	this->explosionTime = explosionTime;
}