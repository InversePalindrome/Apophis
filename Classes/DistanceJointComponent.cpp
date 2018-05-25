/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.cpp
InversePalindrome.com
*/


#include "DistanceJointComponent.hpp"


DistanceJointComponent::DistanceJointComponent(b2World& world, b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchorPointA, const b2Vec2& anchorPointB)
{
	b2DistanceJointDef distanceJointDef;
	distanceJointDef.collideConnected = true;
	distanceJointDef.Initialize(bodyA, bodyB, anchorPointA, anchorPointB);
	
	distanceJoint = static_cast<b2DistanceJoint*>(world.CreateJoint(&distanceJointDef));
}

b2DistanceJoint* DistanceJointComponent::getDistanceJoint()
{
	return distanceJoint;
}

b2DistanceJoint* DistanceJointComponent::getDistanceJoint() const
{
	return distanceJoint;
}