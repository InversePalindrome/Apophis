/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - MenuScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "SettingsScene.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>


bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();
	const auto& windowSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto* background = cocos2d::Sprite::create("SpaceBackground.png");
	background->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	auto* playItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->replaceScene(GameScene::scene()); });

	auto* playLabel = cocos2d::Label::createWithTTF("play", "Zian.ttf", 60.f);
	playLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	playLabel->setPosition(playItem->getContentSize().width / 2.f, playItem->getContentSize().height / 2.f);
	playItem->addChild(playLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"), 
		[director](auto* sender) { director->pushScene(SettingsScene::scene()); });

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
	menu->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	addChild(background);
	addChild(menu);
	
	return true;
}

cocos2d::Scene* MenuScene::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(MenuScene::create());

	return scene;
}