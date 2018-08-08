/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.cpp
InversePalindrome.com
*/


#include "DistanceJointComponent.hpp"

#include <imgui.h>


DistanceJointComponent::DistanceJointComponent(b2Joint* distanceJoint, std::size_t entityIDA, std::size_t entityIDB) :
	JointComponent(distanceJoint, entityIDA, entityIDB),
	distanceJoint(static_cast<b2DistanceJoint*>(distanceJoint))
{
}

void DistanceJointComponent::save(pugi::xml_node& componentNode) const
{
	JointComponent::save(componentNode);

	componentNode.set_name("DistanceJoint");

	componentNode.append_attribute("anchorAX") = distanceJoint->GetAnchorA().x;
	componentNode.append_attribute("anchorAY") = distanceJoint->GetAnchorA().y;
	componentNode.append_attribute("anchorBX") = distanceJoint->GetAnchorB().x;
	componentNode.append_attribute("anchorBY") = distanceJoint->GetAnchorB().y;
}

void DistanceJointComponent::display()
{
	if (ImGui::TreeNode("DistanceJoint"))
	{
		ImGui::TreePop();
	}
}

b2Vec2 DistanceJointComponent::getAnchorA() const
{
	return distanceJoint->GetAnchorA();
}
b2Vec2 DistanceJointComponent::getAnchorB() const
{
	return distanceJoint->GetAnchorB();
}