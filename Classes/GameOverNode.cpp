/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameOverNode.cpp
InversePalindrome.com
*/


#include "GameOverNode.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>


bool GameOverNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();
	const auto windowSize = director->getWinSize();
	
	auto* gameOverLabel = cocos2d::Label::createWithTTF("game over", "Zian.ttf", 80.f);
	gameOverLabel->enableOutline(cocos2d::Color4B(30.f, 144.f, 255.f, 255.f), 6);
	gameOverLabel->setTextColor(cocos2d::Color4B(135.f, 206.f, 250.f, 255.f));
	gameOverLabel->setPosition(windowSize.width / 2.f, windowSize.height / 1.5f);

	auto* playAgainItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[this](auto* sender)
	{
		setVisible(false);
		getEventDispatcher()->dispatchCustomEvent("playAgain");
	});

	auto* playAgainLabel = cocos2d::Label::createWithTTF("play again", "Zian.ttf", 60.f);
	playAgainLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	playAgainLabel->setPosition(playAgainItem->getContentSize().width / 2.f, playAgainItem->getContentSize().height / 2.f);
	playAgainItem->addChild(playAgainLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) {  });

	auto* settingsLabel = cocos2d::Label::createWithTTF("settings", "Zian.ttf", 60.f);
	settingsLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	settingsLabel->setPosition(settingsItem->getContentSize().width / 2.f, settingsItem->getContentSize().height / 2.f);
	settingsItem->addChild(settingsLabel);

	auto* menuItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { });

	auto* menuLabel = cocos2d::Label::createWithTTF("menu", "Zian.ttf", 60.f);
	menuLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	menuLabel->setPosition(menuItem->getContentSize().width / 2.f, menuItem->getContentSize().height / 2.f);
	menuItem->addChild(menuLabel);

	auto* menu = cocos2d::Menu::create(playAgainItem, settingsItem, menuItem, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(windowSize.width / 2.f, windowSize.height / 2.2f);
	
	addChild(gameOverLabel);
	addChild(menu);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("gameOver", [this](auto* event) { setVisible(true); }), this);

	return true;
}