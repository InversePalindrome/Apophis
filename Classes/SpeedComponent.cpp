/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedComponent.cpp
InversePalindrome.com
*/


#include "SpeedComponent.hpp"

#include <imgui.h>


SpeedComponent::SpeedComponent(const pugi::xml_node& componentNode) :
	maxLinearSpeed(10.f),
	maxAngularSpeed(5.f)
{
	if (const auto maxLinearSpeedAttribute = componentNode.attribute("linear"))
	{
		setMaxLinearSpeed(maxLinearSpeedAttribute.as_float());
	}
	if (const auto maxAngularSpeedAttribute = componentNode.attribute("angular"))
	{
		setMaxAngularSpeed(maxAngularSpeedAttribute.as_float());
	}
}

void SpeedComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Speed");

	componentNode.append_attribute("linear") = getMaxLinearSpeed();
	componentNode.append_attribute("angular") = getMaxAngularSpeed();
}

void SpeedComponent::display()
{
	if (ImGui::TreeNode("Speed"))
	{
		ImGui::InputFloat("Max Linear Speed", &maxLinearSpeed);
		ImGui::InputFloat("Max Angular Speed", &maxAngularSpeed);

		ImGui::TreePop();
	}
}

float SpeedComponent::getMaxLinearSpeed() const
{
	return maxLinearSpeed;
}

void SpeedComponent::setMaxLinearSpeed(float maxLinearSpeed)
{
	this->maxLinearSpeed = maxLinearSpeed;
}

float SpeedComponent::getMaxAngularSpeed() const
{
	return maxAngularSpeed;
}

void SpeedComponent::setMaxAngularSpeed(float maxAngularSpeed)
{
	this->maxAngularSpeed = maxAngularSpeed;
}