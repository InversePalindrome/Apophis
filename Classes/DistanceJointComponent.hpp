/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DistanceJointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>


class DistanceJointComponent
{
public:
	explicit DistanceJointComponent(b2DistanceJoint* distanceJoint);

	b2DistanceJoint* getDistanceJoint();
	b2DistanceJoint* getDistanceJoint() const;

private:
	b2DistanceJoint* distanceJoint;
};
