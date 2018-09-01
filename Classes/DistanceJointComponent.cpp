/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.cpp
InversePalindrome.com
*/


#include "DistanceJointComponent.hpp"

#include <imgui.h>


DistanceJointComponent::DistanceJointComponent() :
	distanceJoint(nullptr),
	frequency(0.f),
	dampingRatio(0.f)
{
}

void DistanceJointComponent::load(const pugi::xml_node& componentNode)
{
	JointComponent::load(componentNode);

	if (const auto frequencyAttribute = componentNode.attribute("frequency"))
	{
		setFrequency(frequencyAttribute.as_float());
	}
	if (const auto dampingRatioAttribute = componentNode.attribute("dampingRatio"))
	{
		setDampingRatio(dampingRatioAttribute.as_float());
	}
}

void DistanceJointComponent::save(pugi::xml_node& componentNode) const
{
	JointComponent::save(componentNode);
	
	componentNode.set_name("DistanceJoint");

	componentNode.append_attribute("frequency") = getFrequency();
	componentNode.append_attribute("dampingRatio") = getDampingRatio();
}

void DistanceJointComponent::display()
{
	if (ImGui::TreeNode("DistanceJoint"))
	{
		JointComponent::display();

		ImGui::InputFloat("frequency", &frequency);
		ImGui::InputFloat("dampingRatio", &dampingRatio);

		ImGui::TreePop();
	}
}

b2DistanceJoint* DistanceJointComponent::getDistanceJoint()
{
	return distanceJoint;
}

void DistanceJointComponent::setDistanceJoint(b2DistanceJoint* distanceJoint)
{
	this->distanceJoint = distanceJoint;

	distanceJoint->SetFrequency(frequency);
	distanceJoint->SetDampingRatio(dampingRatio);
}

b2Vec2 DistanceJointComponent::getAnchorA() const
{
	return distanceJoint->GetAnchorA();
}
b2Vec2 DistanceJointComponent::getAnchorB() const
{
	return distanceJoint->GetAnchorB();
}

float DistanceJointComponent::getFrequency() const
{
	return frequency;
}

void DistanceJointComponent::setFrequency(float frequency)
{
	this->frequency = frequency;

	if (distanceJoint)
	{
		distanceJoint->SetFrequency(frequency);
	}
}

float DistanceJointComponent::getDampingRatio() const
{
	return dampingRatio;
}

void DistanceJointComponent::setDampingRatio(float dampingRatio)
{
	this->dampingRatio = dampingRatio;

	if (distanceJoint)
	{
		distanceJoint->SetDampingRatio(dampingRatio);
	}
}