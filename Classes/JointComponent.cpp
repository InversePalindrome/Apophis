/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointComponent.cpp
InversePalindrome.com
*/


#include "JointComponent.hpp"


JointComponent::JointComponent(b2Joint* joint, std::size_t entityIDA, std::size_t entityIDB) : 
	joint(joint),
	entityIDA(entityIDA),
	entityIDB(entityIDB)
{
}

void JointComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.append_attribute("collideConnected") = getCollideConnected();
    componentNode.append_attribute("idA") = entityIDA;
	componentNode.append_attribute("idB") = entityIDB;
}

b2Joint* JointComponent::getJoint()
{
	return joint;
}

b2Joint* JointComponent::getJoint() const
{
	return joint;
}

b2Body* JointComponent::getBodyA()
{
	return joint->GetBodyA();
}

b2Body* JointComponent::getBodyB()
{
	return joint->GetBodyB();
}

std::size_t JointComponent::getEntityIDA() const
{
	return entityIDA;
}

void JointComponent::setEntityIDA(std::size_t entityIDA)
{
	this->entityIDA = entityIDA;
}

std::size_t JointComponent::getEntityIDB() const
{
	return entityIDB;
}

void JointComponent::setEntityIDB(std::size_t entityIDB)
{
	this->entityIDB = entityIDB;
}

bool JointComponent::getCollideConnected() const
{
	return joint->GetCollideConnected();
}