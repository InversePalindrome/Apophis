/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SplashNode.hpp
InversePalindrome.com
*/


#pragma once


#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class SplashNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(SplashNode);

	static cocos2d::Scene* scene();
};