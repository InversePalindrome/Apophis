/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StartNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class StartNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(StartNode);

	static cocos2d::Scene* scene();
};