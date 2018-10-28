/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TargetComponent.cpp
InversePalindrome.com
*/


#include "TargetComponent.hpp"

#include <imgui.h>


TargetComponent::TargetComponent() :
	targetID(-1)
{
}

void TargetComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto targetIDAttribute = componentNode.attribute("id"))
	{
		setTargetID(targetIDAttribute.as_int());
	}
}

void TargetComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Target");

	componentNode.append_attribute("id") = getTargetID();
}

void TargetComponent::display()
{
	if (ImGui::TreeNode("Target"))
	{
		ImGui::InputInt("ID", &targetID);

		ImGui::TreePop();
	}
}

int TargetComponent::getTargetID() const
{
	return targetID;
}

void TargetComponent::setTargetID(int targetID)
{
	this->targetID = targetID;
}