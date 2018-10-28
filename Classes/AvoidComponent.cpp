/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"

#include <imgui.h>


AvoidComponent::AvoidComponent() :
	avoidanceForce(25.f)
{
}

void AvoidComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto avoidanceForceAttribute = componentNode.attribute("force"))
	{
		setAvoidanceForce(avoidanceForceAttribute.as_float());
	}
}

void AvoidComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Avoid");

	componentNode.append_attribute("force") = getAvoidanceForce();
}

void AvoidComponent::display()
{
	if (ImGui::TreeNode("Avoid"))
	{
		ImGui::InputFloat("Force", &avoidanceForce);

		ImGui::TreePop();
	}
}

float AvoidComponent::getAvoidanceForce() const
{
	return avoidanceForce;
}

void AvoidComponent::setAvoidanceForce(float avoidanceForce)
{
	this->avoidanceForce = avoidanceForce;
}