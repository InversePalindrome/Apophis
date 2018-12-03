/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


PatrolComponent::PatrolComponent() :
	pathwayID(0),
	currentPointIndex(0)
{
}

void PatrolComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto pathwayIDAttribute = componentNode.attribute("pathwayID"))
	{
		setPathwayID(pathwayIDAttribute.as_int());
	}
	if (const auto pointIndexAttribute = componentNode.attribute("pointIndex"))
	{
		setCurrentPointIndex(pointIndexAttribute.as_int());
	}
}

void PatrolComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Patrol");

	componentNode.append_attribute("pathwayID") = getPathwayID();
	componentNode.append_attribute("pointIndex") = getCurrentPointIndex();
}

void PatrolComponent::display()
{
	if (ImGui::TreeNode("Patrol"))
	{
		ImGui::InputInt("Pathway ID", &pathwayID);
		ImGui::InputInt("Point Index", &currentPointIndex);

		ImGui::TreePop();
	}
}

int PatrolComponent::getPathwayID() const
{
	return pathwayID;
}

void PatrolComponent::setPathwayID(int pathwayID)
{
	this->pathwayID = pathwayID;
}

int PatrolComponent::getCurrentPointIndex() const
{
	return currentPointIndex;
}

void PatrolComponent::setCurrentPointIndex(int currentPointIndex)
{
	this->currentPointIndex = currentPointIndex;
}