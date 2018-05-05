/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - MenuScene.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCScene.h>


class MenuScene : public cocos2d::Layer
{
public:
	virtual bool init() override;

	CREATE_FUNC(MenuScene);

	static cocos2d::Scene* scene();
};