/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - MenuNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class MenuNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(MenuNode);

	static cocos2d::Scene* scene();
};