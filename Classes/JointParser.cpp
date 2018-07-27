/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointParser.cpp
InversePalindrome.com
*/


#include "JointParser.hpp"


void JointParser::parseJointDef(b2JointDef& jointDef, const pugi::xml_node& jointNode)
{
	if (const auto collideConnectedAttribute = jointNode.attribute("collideConnected"))
	{
		jointDef.collideConnected = collideConnectedAttribute.as_bool();
	}
}

void JointParser::parseDistanceJointDef(b2DistanceJointDef& distanceJointDef, b2Body* bodyA, b2Body* bodyB, const pugi::xml_node& jointNode)
{
	parseJointDef(distanceJointDef, jointNode);

	b2Vec2 anchorA(0.f, 0.f);
	b2Vec2 anchorB(0.f, 0.f);

	if (const auto anchorAXAttribute = jointNode.attribute("anchorAX"))
	{
		anchorA.x = anchorAXAttribute.as_float();
	}
	if (const auto anchorAYAttribute = jointNode.attribute("anchorAY"))
	{
		anchorA.y = anchorAYAttribute.as_float();
	}
	if (const auto anchorBXAttribute = jointNode.attribute("anchorBX"))
	{
		anchorB.x = anchorBXAttribute.as_float();
	}
	if (const auto anchorBYAttribute = jointNode.attribute("anchorBY"))
	{
		anchorB.y = anchorBYAttribute.as_float();
	}

	distanceJointDef.Initialize(bodyA, bodyB, anchorA, anchorB);
}