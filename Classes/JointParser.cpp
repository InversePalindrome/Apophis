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

	b2Vec2 localAnchorA(0.f, 0.f);
	b2Vec2 localAnchorB(0.f, 0.f);

	if (const auto anchorAXAttribute = jointNode.attribute("jointAX"))
	{
		localAnchorA.x = anchorAXAttribute.as_float();
	}
	if (const auto anchorAYAttribute = jointNode.attribute("jointAY"))
	{
		localAnchorA.y = anchorAYAttribute.as_float();
	}
	if (const auto anchorBXAttribute = jointNode.attribute("jointBX"))
	{
		localAnchorB.x = anchorBXAttribute.as_float();
	}
	if (const auto anchorBYAttribute = jointNode.attribute("jointBY"))
	{
		localAnchorB.y = anchorBYAttribute.as_float();
	}

	distanceJointDef.Initialize(bodyA, bodyB, localAnchorA, localAnchorB);
}