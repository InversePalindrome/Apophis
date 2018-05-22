/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>


class DistanceJointComponent
{
public:
	DistanceJointComponent(b2World& world, b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchorPointA, const b2Vec2& anchorPointB);

	b2DistanceJoint* getDistanceJoint();
	b2DistanceJoint* getDistanceJoint() const;

private:
	b2DistanceJoint* distanceJoint;
};
