/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ArriveComponent.cpp
InversePalindrome.com
*/


#include "ArriveComponent.hpp"

#include <imgui.h>


ArriveComponent::ArriveComponent() :
	slowRadius(5.f)
{
}

void ArriveComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto slowRadiusAttribute = componentNode.attribute("slowRadius"))
	{
		setSlowRadius(slowRadiusAttribute.as_float());
	}
}

void ArriveComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Arrive");

	componentNode.append_attribute("slowRadius") = getSlowRadius();
}

void ArriveComponent::display()
{
	if (ImGui::TreeNode("Arrive"))
	{
		ImGui::InputFloat("Slow Radius", &slowRadius);

		ImGui::TreePop();
	}
}

float ArriveComponent::getSlowRadius() const
{
	return slowRadius;
}

void ArriveComponent::setSlowRadius(float slowRadius)
{
	this->slowRadius = slowRadius;
}