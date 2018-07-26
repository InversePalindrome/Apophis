/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointComponent.cpp
InversePalindrome.com
*/


#include "JointComponent.hpp"


JointComponent::JointComponent(b2Joint* joint) : 
	joint(joint)
{
}

void JointComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.append_attribute("collideConnected") = getCollideConnected();
}

b2Joint* JointComponent::getJoint()
{
	return joint;
}

b2Joint* JointComponent::getJoint() const
{
	return joint;
}

bool JointComponent::getCollideConnected() const
{
	return joint->GetCollideConnected();
}