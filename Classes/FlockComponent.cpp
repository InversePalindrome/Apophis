/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.cpp
InversePalindrome.com
*/


#include "FlockComponent.hpp"

#include <imgui.h>


FlockComponent::FlockComponent() :
	groupID(-1),
	groupRadius(3.f),
	alignmentForce(5.f),
	cohesionForce(5.f),
	separationForce(5.f)
{
}

void FlockComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto groupIDAttribute = componentNode.attribute("id"))
	{
		setGroupID(groupIDAttribute.as_int());
	}
	if (const auto groupRadiusAttribute = componentNode.attribute("groupRadius"))
	{
		setGroupRadius(groupRadiusAttribute.as_float());
	}
	if (const auto alignmentForceAttribute = componentNode.attribute("alignmentForce"))
	{
		setAlignmentForce(alignmentForceAttribute.as_float());
	}
	if (const auto cohesionForceAttribute = componentNode.attribute("cohesionForce"))
	{
		setCohesionForce(cohesionForceAttribute.as_float());
	}
	if (const auto separationForceAttribute = componentNode.attribute("separationForce"))
	{
		setSeparationForce(separationForceAttribute.as_float());
	}
}

void FlockComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Flock");

	componentNode.append_attribute("id") = getGroupID();
	componentNode.append_attribute("groupRadius") = getGroupRadius();
	componentNode.append_attribute("alignmentForce") = getAlignmentForce();
	componentNode.append_attribute("cohesionForce") = getCohesionForce();
	componentNode.append_attribute("separationForce") = getSeparationForce();
}

void FlockComponent::display()
{
	if (ImGui::TreeNode("Flock"))
	{
		ImGui::InputInt("Group ID", &groupID);
		ImGui::InputFloat("Group Radius", &groupRadius);
		ImGui::InputFloat("Alignment Force", &alignmentForce);
		ImGui::InputFloat("Cohesion Force", &cohesionForce);
		ImGui::InputFloat("Separation Force", &separationForce);

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

float FlockComponent::getAlignmentForce() const
{
	return alignmentForce;
}

void FlockComponent::setAlignmentForce(float alignmentForce)
{
	this->alignmentForce = alignmentForce;
}

float FlockComponent::getCohesionForce() const
{
	return cohesionForce;
}

void FlockComponent::setCohesionForce(float cohesionForce)
{
	this->cohesionForce = cohesionForce;
}

float FlockComponent::getSeparationForce() const
{
	return separationForce;
}

void FlockComponent::setSeparationForce(float separationForce)
{
	this->separationForce = separationForce;
}