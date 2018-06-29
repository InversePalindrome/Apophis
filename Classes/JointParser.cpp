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

void JointParser::parseDistanceJointDef(b2DistanceJointDef& distanceJointDef, const pugi::xml_node& jointNode)
{
	parseJointDef(distanceJointDef, jointNode);

	if (const auto anchorAXAttribute = jointNode.attribute("jointAX"))
	{
		distanceJointDef.localAnchorA.x = anchorAXAttribute.as_float();
	}
	if (const auto anchorAYAttribute = jointNode.attribute("jointAY"))
	{
		distanceJointDef.localAnchorA.y = anchorAYAttribute.as_float();
	}
	if (const auto anchorBXAttribute = jointNode.attribute("jointBX"))
	{
		distanceJointDef.localAnchorB.x = anchorBXAttribute.as_float();
	}
	if (const auto anchorBYAttribute = jointNode.attribute("jointBY"))
	{
		distanceJointDef.localAnchorB.y = anchorBYAttribute.as_float();
	}
}