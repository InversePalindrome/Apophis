/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HudNode.cpp
InversePalindrome.com
*/


#include "HudNode.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/ui/UILoadingBar.h>
#include <cocos/base/CCEventCustom.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>


bool HudNode::init()
{
	if (!Node::init())
	{
		return false;
	}

    const auto windowSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto* healthBar = cocos2d::ui::LoadingBar::create("Bar", cocos2d::ui::Widget::TextureResType::PLIST, 100.f);
	healthBar->setPosition({ windowSize.width / 6.f, windowSize.height / 1.025f });

	addChild(healthBar, 0, "HealthBar");

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("setHealthBar", [healthBar](auto* event) { healthBar->setPercent(*static_cast<float*>(event->getUserData())); }), this);

	return true;
}