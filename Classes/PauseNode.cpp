/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PauseNode.cpp
InversePalindrome.com
*/


#include "PauseNode.hpp"
#include "SettingsNode.hpp"
#include "LevelSelectionNode.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>


bool PauseNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();

	auto* resumeItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[this](auto* sender)
	{
		setVisible(false);
		getEventDispatcher()->dispatchCustomEvent("resume");
	});
	
	auto* resumeLabel = cocos2d::Label::createWithTTF("resume", "Zian.ttf", 60.f);
	resumeLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	resumeLabel->setPosition(resumeItem->getContentSize().width / 2.f, resumeItem->getContentSize().height / 2.f);
	resumeItem->addChild(resumeLabel);

	auto* retryItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[this](auto* sender)
	{
		setVisible(false);
		getEventDispatcher()->dispatchCustomEvent("playAgain");
	});

	auto* retryLabel = cocos2d::Label::createWithTTF("retry", "Zian.ttf", 60.f);
	retryLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	retryLabel->setPosition(retryItem->getContentSize().width / 2.f, retryItem->getContentSize().height / 2.f);
	retryItem->addChild(retryLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->pushScene(SettingsNode::scene()); });

	auto* settingsLabel = cocos2d::Label::createWithTTF("settings", "Zian.ttf", 60.f);
	settingsLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	settingsLabel->setPosition(settingsItem->getContentSize().width / 2.f, settingsItem->getContentSize().height / 2.f);
	settingsItem->addChild(settingsLabel);

	auto* quitItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->replaceScene(LevelSelectionNode::scene()); });

	auto* quitLabel = cocos2d::Label::createWithTTF("quit", "Zian.ttf", 60.f);
	quitLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	quitLabel->setPosition(quitItem->getContentSize().width / 2.f, quitItem->getContentSize().height / 2.f);
	quitItem->addChild(quitLabel);

	auto* menu = cocos2d::Menu::create(resumeItem, retryItem, settingsItem, quitItem, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(director->getWinSize().width / 2.f, director->getWinSize().height / 2.f);

	addChild(menu);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("pause", [this](auto* event) { setVisible(true); }), this);

	return true;
}