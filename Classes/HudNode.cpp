/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HudNode.cpp
InversePalindrome.com
*/


#include "HudNode.hpp"

#include <cocos/base/CCDirector.h>


HudNode::~HudNode()
{
	healthBar->release();
}

bool HudNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	const auto& windowSize = cocos2d::Director::getInstance()->getVisibleSize();

    healthBar = cocos2d::ui::LoadingBar::create("Bar", cocos2d::ui::Widget::TextureResType::PLIST, 100.f);
	healthBar->setPosition({ windowSize.width / 6.f, windowSize.height / 1.025f });
	healthBar->retain();

	addChild(healthBar, 0, "HealthBar");

	return true;
}

cocos2d::ui::LoadingBar* HudNode::getHealthBar()
{
	return healthBar;
}