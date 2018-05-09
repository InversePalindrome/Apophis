/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - HudNode.cpp
InversePalindrome.com
*/


#include "HudNode.hpp"

#include <cocos/ui/UILoadingBar.h>
#include <cocos/base/CCDirector.h>


bool HudNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	const auto* director = cocos2d::Director::getInstance();
	const auto& windowSize = director->getVisibleSize();

	auto* healthBar = cocos2d::ui::LoadingBar::create("Bar", cocos2d::ui::Widget::TextureResType::PLIST, 100.f);
	healthBar->setPosition({ windowSize.width / 6.f, windowSize.height / 1.025f });

	addChild(healthBar, 0, "HealthBar");

	return true;
}