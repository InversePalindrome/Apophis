/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnchorPointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <pugixml.hpp>


class AnchorPointComponent
{
public:
	explicit AnchorPointComponent(const pugi::xml_node& componentNode);

	b2Vec2 getAnchorPoint() const;
	void setAnchorPoint(const b2Vec2& anchorPoint);

private:
	b2Vec2 anchorPoint;
};