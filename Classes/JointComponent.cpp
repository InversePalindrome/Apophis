/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointComponent.cpp
InversePalindrome.com
*/


#include "JointComponent.hpp"

#include <imgui.h>


JointComponent::JointComponent() : 
	joint(nullptr),
	entityIDA(0),
	entityIDB(0),
	localAnchorA(0.f, 0.f),
	localAnchorB(0.f, 0.f)
{
}

void JointComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto idAAttribute = componentNode.attribute("idA"))
	{
		setEntityIDA(idAAttribute.as_int());
	}
	if (const auto idBAttribute = componentNode.attribute("idB"))
	{
		setEntityIDB(idBAttribute.as_int());
	}
	if (const auto anchorAXAttribute = componentNode.attribute("anchorAX"),
		anchorAYAttribute = componentNode.attribute("anchorAY");
	    anchorAXAttribute && anchorAYAttribute)
	{
		setLocalAnchorA({ anchorAXAttribute.as_float(), anchorAYAttribute.as_float() });
	}
	if (const auto anchorBXAttribute = componentNode.attribute("anchorBX"),
		anchorBYAttribyte = componentNode.attribute("anchorBY");
	    anchorBXAttribute && anchorBYAttribyte)
	{
		setLocalAnchorB({ anchorBXAttribute.as_float(), anchorBYAttribyte.as_float() });
	}
}

void JointComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.append_attribute("idA") = getEntityIDA();
	componentNode.append_attribute("idB") = getEntityIDB();
	componentNode.append_attribute("anchorAX") = getLocalAnchorA().x;
	componentNode.append_attribute("anchorAY") = getLocalAnchorA().y;
	componentNode.append_attribute("anchorBX") = getLocalAnchorB().x;
	componentNode.append_attribute("anchorBY") = getLocalAnchorB().y;
}

void JointComponent::display()
{
	if (ImGui::TreeNode("Joint"))
	{
		ImGui::InputInt("ID A", &entityIDA);
		ImGui::InputInt("ID B", &entityIDB);
		ImGui::InputFloat2("Anchor A", &localAnchorA.x);
		ImGui::InputFloat2("Anchor B", &localAnchorB.x);

		ImGui::TreePop();
	}
}

b2Joint* JointComponent::getJoint()
{
	return joint;
}

b2Joint* JointComponent::getJoint() const
{
	return joint;
}

void JointComponent::setJoint(b2Joint* joint)
{
	this->joint = joint;
}

b2Body* JointComponent::getBodyA()
{
	return joint->GetBodyA();
}

b2Body* JointComponent::getBodyB()
{
	return joint->GetBodyB();
}

int JointComponent::getEntityIDA() const
{
	return entityIDA;
}

void JointComponent::setEntityIDA(int entityIDA)
{
	this->entityIDA = entityIDA;
}

int JointComponent::getEntityIDB() const
{
	return entityIDB;
}

void JointComponent::setEntityIDB(int entityIDB)
{
	this->entityIDB = entityIDB;
}

b2Vec2 JointComponent::getLocalAnchorA() const
{
	return localAnchorA;
}

void JointComponent::setLocalAnchorA(const b2Vec2& localAnchorA)
{
	this->localAnchorA = localAnchorA;
}

b2Vec2 JointComponent::getLocalAnchorB() const
{
	return localAnchorB;
}

void JointComponent::setLocalAnchorB(const b2Vec2& localAnchorB)
{
	this->localAnchorB = localAnchorB;
}