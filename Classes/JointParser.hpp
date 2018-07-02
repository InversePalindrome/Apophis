/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointParser.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>

#include <pugixml.hpp>


namespace JointParser
{
	void parseJointDef(b2JointDef& jointDef, const pugi::xml_node& jointNode);
	void parseDistanceJointDef(b2DistanceJointDef& distanceJointDef, b2Body* bodyA, b2Body* bodyB, const pugi::xml_node& jointNode);
}