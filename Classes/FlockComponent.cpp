/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"

#include <imgui.h>


FlockComponent::FlockComponent() :
	groupID(-1),
	groupRadius(25.f)
{
}

void FlockComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto groupIDAttribute = componentNode.attribute("id"))
	{
		setGroupID(groupIDAttribute.as_int());
	}
	if (const auto groupRadiusAttribute = componentNode.attribute("radius"))
	{
		setGroupRadius(groupRadiusAttribute.as_float());
	}
}

void FlockComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Flock");

	componentNode.append_attribute("id") = getGroupID();
	componentNode.append_attribute("radius") = getGroupRadius();
}

void FlockComponent::display()
{
	if (ImGui::TreeNode("Flock"))
	{
		ImGui::InputInt("Group ID", &groupID);
		ImGui::InputFloat("Radius", &groupRadius);

		ImGui::TreePop();
	}
}

int FlockComponent::getGroupID() const
{
	return groupID;
}

void FlockComponent::setGroupID(int groupID)
{
	this->groupID = groupID;
}

float FlockComponent::getGroupRadius() const
{
	return groupRadius;
}

void FlockComponent::setGroupRadius(float groupRadius)
{
	this->groupRadius = groupRadius;
}