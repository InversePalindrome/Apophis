/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnchorPointComponent.cpp
InversePalindrome.com
*/


#include "AnchorPointComponent.hpp"

#include <string>


AnchorPointComponent::AnchorPointComponent(const tinyxml2::XMLElement* componentNode) :
	anchorPoint(0.f, 0.f)
{
	if (const auto* x = componentNode->Attribute("x"))
	{
		anchorPoint.x = std::stof(x);
	}
	if (const auto* y = componentNode->Attribute("y"))
	{
		anchorPoint.y = std::stof(y);
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