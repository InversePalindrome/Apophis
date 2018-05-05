/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - FlockingBehaviors.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

#include <vector>


namespace FlockingBehaviors
{
	void align(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed);
	void cohesion(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed);
	void separate(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed);
} 