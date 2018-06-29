/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.cpp
InversePalindrome.com
*/


#include "DistanceJointComponent.hpp"


DistanceJointComponent::DistanceJointComponent(b2DistanceJoint* distanceJoint) :
	distanceJoint(distanceJoint)
{
}

b2DistanceJoint* DistanceJointComponent::getDistanceJoint()
{
	return distanceJoint;
}

b2DistanceJoint* DistanceJointComponent::getDistanceJoint() const
{
	return distanceJoint;
}