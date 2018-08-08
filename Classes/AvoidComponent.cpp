/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AvoidComponent.cpp
InversePalindrome.com
*/


#include "AvoidComponent.hpp"

#include <imgui.h>


AvoidComponent::AvoidComponent(const pugi::xml_node& componentNode) :
	avoidanceAheadDistance(10.f),
	avoidanceForce(50.f)
{
	if (const auto distanceAttribute = componentNode.attribute("distance"))
	{
		setAvoidanceAheadDistance(distanceAttribute.as_float());
	}
	if (const auto avoidanceForceAttribute = componentNode.attribute("force"))
	{
	    setAvoidanceForce(avoidanceForceAttribute.as_float());
	}
}

void AvoidComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Avoid");

	componentNode.append_attribute("distance") = getAvoidanceAheadDistance();
	componentNode.append_attribute("force") = getAvoidanceForce();
}

void AvoidComponent::display()
{
	if (ImGui::TreeNode("Avoid"))
	{
		ImGui::InputFloat("distance", &avoidanceForce);
		ImGui::InputFloat("force", &avoidanceForce);

		ImGui::TreePop();
	}
}

float AvoidComponent::getAvoidanceAheadDistance() const
{
	return avoidanceAheadDistance;
}

void AvoidComponent::setAvoidanceAheadDistance(float avoidanceAheadDistance)
{
	this->avoidanceAheadDistance = avoidanceAheadDistance;
}

float AvoidComponent::getAvoidanceForce() const
{
	return avoidanceForce;
}

void AvoidComponent::setAvoidanceForce(float avoidanceForce)
{
	this->avoidanceForce = avoidanceForce;
}