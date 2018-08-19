/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DamageComponent.cpp
InversePalindrome.com
*/


#include "DamageComponent.hpp"

#include <imgui.h>


DamageComponent::DamageComponent() :
	damageHitpoints(1.f)
{
}

void DamageComponent::load(const pugi::xml_node& componentNode)
{
	setDamageHitpoints(componentNode.text().as_float());
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
		ImGui::InputFloat("Hitpoints", &damageHitpoints);

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