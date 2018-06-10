/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnchorPointComponent.cpp
InversePalindrome.com
*/


#include "AnchorPointComponent.hpp"


AnchorPointComponent::AnchorPointComponent(const pugi::xml_node& componentNode) :
	anchorPoint(0.f, 0.f)
{
	if (const auto xAttribute = componentNode.attribute("x"))
	{
		anchorPoint.x = xAttribute.as_float();
	}
	if (const auto yAttribute = componentNode.attribute("y"))
	{
		anchorPoint.y = yAttribute.as_float();
	}
}

b2Vec2 AnchorPointComponent::getAnchorPoint() const
{
	return anchorPoint;
}

void AnchorPointComponent::setAnchorPoint(const b2Vec2& anchorPoint)
{
	this->anchorPoint = anchorPoint;
}