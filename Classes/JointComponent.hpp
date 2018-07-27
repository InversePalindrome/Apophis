/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/Joints/b2Joint.h>

#include <pugixml.hpp>


class JointComponent
{
public:
	explicit JointComponent(b2Joint* joint, std::size_t entityIDA, std::size_t entityIDB);

	void save(pugi::xml_node& componentNode) const;

	b2Joint* getJoint();
	b2Joint* getJoint() const;

	b2Body* getBodyA();
	b2Body* getBodyB();

	std::size_t getEntityIDA() const;
	void setEntityIDA(std::size_t entityIDA);

	std::size_t getEntityIDB() const;
	void setEntityIDB(std::size_t entityIDB);

	bool getCollideConnected() const;

private:
	b2Joint* joint;
	std::size_t entityIDA;
	std::size_t entityIDB;
};