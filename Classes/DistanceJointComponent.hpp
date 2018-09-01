/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "JointComponent.hpp"

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>

#include <pugixml.hpp>


class DistanceJointComponent : public JointComponent
{
public:
	DistanceJointComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	b2DistanceJoint* getDistanceJoint();
	void setDistanceJoint(b2DistanceJoint* distanceJoint);

	b2Vec2 getAnchorA() const;
	b2Vec2 getAnchorB() const;

	float getFrequency() const;
	void setFrequency(float frequency);

	float getDampingRatio() const;
	void setDampingRatio(float dampingRatio);

private:
	b2DistanceJoint* distanceJoint;

	float frequency;
	float dampingRatio;
};
