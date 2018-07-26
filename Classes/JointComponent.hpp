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
	explicit JointComponent(b2Joint* joint);

	void save(pugi::xml_node& componentNode) const;

	b2Joint* getJoint();
	b2Joint* getJoint() const;

	bool getCollideConnected() const;

private:
	b2Joint* joint;
};