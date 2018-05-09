/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - MenuNode.cpp
InversePalindrome.com
*/


#include "MenuNode.hpp"
#include "GameScene.hpp"
#include "SettingsNode.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>


bool MenuNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();

	auto* background = cocos2d::Sprite::create("SpaceBackground.png");
	background->setPosition(director->getWinSize().width / 2.f, director->getWinSize().height / 2.f);

	auto* playItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->replaceScene(GameScene::create()); });

	auto* playLabel = cocos2d::Label::createWithTTF("play", "Zian.ttf", 60.f);
	playLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	playLabel->setPosition(playItem->getContentSize().width / 2.f, playItem->getContentSize().height / 2.f);
	playItem->addChild(playLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"), 
		[director](auto* sender) { director->pushScene(SettingsNode::scene()); });

	auto* settingsLabel = cocos2d::Label::createWithTTF("settings", "Zian.ttf", 60.f);
	settingsLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	settingsLabel->setPosition(settingsItem->getContentSize().width / 2.f, settingsItem->getContentSize().height / 2.f);
	settingsItem->addChild(settingsLabel);

	auto* exitItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"), 
		[director](auto* sender) {	director->end(); });

	auto* exitLabel = cocos2d::Label::createWithTTF("exit", "Zian.ttf", 60.f);
	exitLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	exitLabel->setPosition(exitItem->getContentSize().width / 2.f, exitItem->getContentSize().height / 2.f);
	exitItem->addChild(exitLabel);

	auto* menu = cocos2d::Menu::create(playItem, settingsItem, exitItem, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(director->getWinSize().width / 2.f, director->getWinSize().height / 2.f);

	addChild(background);
	addChild(menu);
	
	return true;
}

cocos2d::Scene* MenuNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(MenuNode::create());

	return scene;
}