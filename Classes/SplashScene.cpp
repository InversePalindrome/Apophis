/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SplashScene.cpp
InversePalindrome.com
*/


#include "StartScene.hpp"
#include "SplashScene.hpp"

#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>


bool SplashScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	const auto& windowSize = cocos2d::Director::getInstance()->getWinSize();

	auto* logo = cocos2d::Sprite::create("InversePalindromeLogo.png");
	logo->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	addChild(logo);
	
	scheduleOnce([](float dt) { cocos2d::Director::getInstance()->replaceScene(StartScene::scene()); }, 2.f, "Splash");

	return true;
}

cocos2d::Scene* SplashScene::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(SplashScene::create());

	return scene;
}