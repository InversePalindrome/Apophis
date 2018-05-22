/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnchorPointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <Box2D/Common/b2Math.h>


class AnchorPointComponent
{
public:
	explicit AnchorPointComponent(const tinyxml2::XMLElement* componentNode);

	b2Vec2 getAnchorPoint() const;
	void setAnchorPoint(const b2Vec2& anchorPoint);

private:
	b2Vec2 anchorPoint;
};