/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "JointComponent.hpp"

#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>

#include <pugixml.hpp>


class DistanceJointComponent : public JointComponent
{
public:
	explicit DistanceJointComponent(b2Joint* distanceJoint);

	void save(pugi::xml_node& componentNode) const;

	b2Vec2 getAnchorA() const;
	b2Vec2 getAnchorB() const;

private:
	b2DistanceJoint* distanceJoint;
};
