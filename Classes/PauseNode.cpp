/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PauseNode.cpp
InversePalindrome.com
*/


#include "MenuNode.hpp"
#include "GameScene.hpp"
#include "PauseNode.hpp"
#include "SettingsNode.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>


bool PauseNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();

	auto* resumeItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[this, director](auto* sender)
	{
		director->getRunningScene()->scheduleUpdate();
		setVisible(false);
	});

	auto* resumeLabel = cocos2d::Label::createWithTTF("resume", "Zian.ttf", 60.f);
	resumeLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	resumeLabel->setPosition(resumeItem->getContentSize().width / 2.f, resumeItem->getContentSize().height / 2.f);
	resumeItem->addChild(resumeLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->pushScene(SettingsNode::scene()); });

	auto* settingsLabel = cocos2d::Label::createWithTTF("settings", "Zian.ttf", 60.f);
	settingsLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	settingsLabel->setPosition(settingsItem->getContentSize().width / 2.f, settingsItem->getContentSize().height / 2.f);
	settingsItem->addChild(settingsLabel);

	auto* quitItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->replaceScene(MenuNode::scene()); });

	auto* quitLabel = cocos2d::Label::createWithTTF("quit", "Zian.ttf", 60.f);
	quitLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	quitLabel->setPosition(quitItem->getContentSize().width / 2.f, quitItem->getContentSize().height / 2.f);
	quitItem->addChild(quitLabel);

	auto* menu = cocos2d::Menu::create(resumeItem, settingsItem, quitItem, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(director->getWinSize().width / 2.f, director->getWinSize().height / 2.f);

	addChild(menu);

	setVisible(false);

	return true;
}