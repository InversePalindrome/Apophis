/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AccelerationComponent.cpp
InversePalindrome.com
*/


#include "AccelerationComponent.hpp"

#include <imgui.h>


AccelerationComponent::AccelerationComponent(const pugi::xml_node& componentNode) :
	linearAcceleration(1.f),
	angularAcceleration(1.f)
{
	if (const auto linearAccelerationAttribute = componentNode.attribute("linear"))
	{
		setLinearAcceleration(linearAccelerationAttribute.as_float());
	}
	if (const auto angularAccelerationAttribute = componentNode.attribute("angular"))
	{
		setAngularAcceleration(angularAccelerationAttribute.as_float());
	}
}

void AccelerationComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Acceleration");

	componentNode.append_attribute("linear") = getLinearAcceleration();
	componentNode.append_attribute("angular") = getAngularAcceleration();
}

void AccelerationComponent::display()
{
	if (ImGui::TreeNode("Acceleration"))
	{
		ImGui::InputFloat("Linear Acceleration", &linearAcceleration);
		ImGui::InputFloat("Angular Acceleration", &angularAcceleration);

		ImGui::TreePop();
	}
}

float AccelerationComponent::getLinearAcceleration() const
{
	return linearAcceleration;
}

void AccelerationComponent::setLinearAcceleration(float linearAcceleration)
{
	this->linearAcceleration = linearAcceleration;
}

float AccelerationComponent::getAngularAcceleration() const
{
	return angularAcceleration;
}

void AccelerationComponent::setAngularAcceleration(float angularAcceleration)
{
	this->angularAcceleration = angularAcceleration;
}