/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SplashNode.cpp
InversePalindrome.com
*/


#include "StartNode.hpp"
#include "SplashNode.hpp"

#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>


bool SplashNode::init()
{
	if (!Node::init())
	{
		return false;
	}

    auto* director = cocos2d::Director::getInstance();

	auto* logo = cocos2d::Sprite::create("InversePalindromeLogo.png");
	logo->setPosition(director->getWinSize().width / 2.f, director->getWinSize().height / 2.f);

	addChild(logo);
	
	scheduleOnce([director](float dt) { director->replaceScene(StartNode::scene()); }, 2.f, "Splash");

	return true;
}

cocos2d::Scene* SplashNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(SplashNode::create());

	return scene;
}