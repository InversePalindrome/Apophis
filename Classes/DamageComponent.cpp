/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DamageComponent.cpp
InversePalindrome.com
*/


#include "DamageComponent.hpp"

#include <imgui.h>


DamageComponent::DamageComponent(const pugi::xml_node& componentNode) :
	damageHitpoints(componentNode.text().as_float(1.f))
{
}

void DamageComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Damage");

	componentNode.text().set(damageHitpoints);
}

void DamageComponent::display()
{
	if (ImGui::TreeNode("Damage"))
	{
		ImGui::InputFloat("hitpoints", &damageHitpoints);

		ImGui::TreePop();
	}
}

float DamageComponent::getDamageHitpoints() const
{
	return damageHitpoints;
}

void DamageComponent::setDamageHitpoints(float hitpoints)
{
	this->damageHitpoints = hitpoints;
}