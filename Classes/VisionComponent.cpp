/*
Copyright (c) 2018 Inverse Palindrome
Apophis - VisionComponent.cpp
InversePalindrome.com
*/


#include "VisionComponent.hpp"

#include <imgui.h>


VisionComponent::VisionComponent(const pugi::xml_node& componentNode) :
	visionDistance(componentNode.text().as_float(10.f))
{
}

void VisionComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Vision");

	componentNode.text().set(getVisionDistance());
}

void VisionComponent::display()
{
	if (ImGui::TreeNode("Vision"))
	{
		ImGui::InputFloat("Distance", &visionDistance);

		ImGui::TreePop();
	}
}

float VisionComponent::getVisionDistance() const
{
	return visionDistance;
}

void VisionComponent::setVisionDistance(float visionDistance)
{
	this->visionDistance = visionDistance;
}