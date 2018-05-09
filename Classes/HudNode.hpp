/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - HudNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>


class HudNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(HudNode);
};