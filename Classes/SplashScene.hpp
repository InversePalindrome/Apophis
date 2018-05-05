/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SplashScene.hpp
InversePalindrome.com
*/


#pragma once


#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCScene.h>


class SplashScene : public cocos2d::Layer
{
public:
	virtual bool init() override;

	CREATE_FUNC(SplashScene);

	static cocos2d::Scene* scene();
};