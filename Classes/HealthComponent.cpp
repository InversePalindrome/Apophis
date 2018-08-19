/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HealthComponent.cpp
InversePalindrome.com
*/


#include "HealthComponent.hpp"

#include <imgui.h>


HealthComponent::HealthComponent() :
	maxHitpoints(5.f),
	currentHitpoints(5.f)
{
}

void HealthComponent::load(const pugi::xml_node& componentNode)
{
	setMaxHitpoints(componentNode.text().as_float());
	setCurrentHitpoints(componentNode.text().as_float());
}

void HealthComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Health");

	componentNode.text().set(maxHitpoints);
}

void HealthComponent::display()
{
	if (ImGui::TreeNode("Health"))
	{
		ImGui::InputFloat("Max Hitpoints", &maxHitpoints);

		ImGui::TreePop();
	}
}

float HealthComponent::getMaxHitpoints() const
{
	return maxHitpoints;
}

void HealthComponent::setMaxHitpoints(float maxHitpoints)
{
	this->maxHitpoints = maxHitpoints;
}

float HealthComponent::getCurrentHitpoints() const
{
	return currentHitpoints;
}

void HealthComponent::setCurrentHitpoints(float currentHitpoints)
{
	this->currentHitpoints = currentHitpoints;
}