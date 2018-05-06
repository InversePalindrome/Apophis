/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - GameScene.cpp
InversePalindrome.com
*/


#include "GameScene.hpp"
#include "MenuScene.hpp"
#include "InputSystem.hpp"
#include "AudioSystem.hpp"
#include "Application.hpp"
#include "CombatSystem.hpp"
#include "PhysicsSystem.hpp"
#include "EntityFactory.hpp"
#include "SettingsScene.hpp"
#include "BehaviorSystem.hpp"
#include "GraphicsSystem.hpp"

#include <cocos/2d/CCMenu.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCMenuItem.h>
#include <cocos/base/CCDirector.h>


GameScene::GameScene() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	entityFactory(entityManager, eventManager),
	map(entityFactory, eventManager)
{
}

GameScene::~GameScene()
{
	keyboardManager->release();
	mouseManager->release();
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	scheduleUpdate();

	keyboardManager = KeyboardManager::create();
	keyboardManager->retain();

	mouseManager = MouseManager::create();
	mouseManager->retain();

	addChild(keyboardManager);
	addChild(mouseManager);

	map.init(this);
	
	initSystems();

	map.load("Andromeda");
	entityFactory.createEntity("UFO");
	entityFactory.createEntity("SpaceCruiser");
	entityFactory.createEntity("SpaceCruiser");
	entityFactory.createEntity("SpaceCruiser");
	entityFactory.createEntity("Star");

	return true;
}

void GameScene::update(float dt)
{
	if (keyboardManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		unscheduleUpdate();
		getParent()->addChild(createPauseMenu());
	}
	if (keyboardManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_CTRL) && keyboardManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_Z))
	{
		auto* director = cocos2d::Director::getInstance();

		director->setDisplayStats(!director->isDisplayStats());
	}

	systemManager.update_all(dt);
}

cocos2d::Scene* GameScene::scene()
{
	auto* scene = cocos2d::Scene::createWithPhysics();
	scene->addChild(GameScene::create());

	return scene;
}

cocos2d::Layer* GameScene::createPauseMenu()
{
	auto* pauseMenu = cocos2d::Layer::create();

	auto* director = cocos2d::Director::getInstance();
	const auto& windowSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto* resumeItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[this, pauseMenu](auto* sender) 
	{
		scheduleUpdate();
		pauseMenu->removeFromParentAndCleanup(true);
	});

	auto* resumeLabel = cocos2d::Label::createWithTTF("resume", "Zian.ttf", 60.f);
	resumeLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	resumeLabel->setPosition(resumeItem->getContentSize().width / 2.f, resumeItem->getContentSize().height / 2.f);
	resumeItem->addChild(resumeLabel);

	auto* settingsItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->pushScene(SettingsScene::scene()); });

	auto* settingsLabel = cocos2d::Label::createWithTTF("settings", "Zian.ttf", 60.f);
	settingsLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	settingsLabel->setPosition(settingsItem->getContentSize().width / 2.f, settingsItem->getContentSize().height / 2.f);
	settingsItem->addChild(settingsLabel);

	auto* quitItem = cocos2d::MenuItemSprite::create(cocos2d::Sprite::createWithSpriteFrameName("RegularRectangleButton"), cocos2d::Sprite::createWithSpriteFrameName("SelectedRectangleButton"),
		[director](auto* sender) { director->replaceScene(MenuScene::scene()); });

	auto* quitLabel = cocos2d::Label::createWithTTF("quit", "Zian.ttf", 60.f);
	quitLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	quitLabel->setPosition(quitItem->getContentSize().width / 2.f, quitItem->getContentSize().height / 2.f);
	quitItem->addChild(quitLabel);

	auto* menu = cocos2d::Menu::create(resumeItem, settingsItem, quitItem, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	pauseMenu->addChild(menu);

	return pauseMenu;
}

void GameScene::initSystems()
{
	systemManager.add<AudioSystem>();
	systemManager.add<BehaviorSystem>();
	systemManager.add<PhysicsSystem>(this, eventManager);
	systemManager.add<CombatSystem>(this, entityFactory);
	systemManager.add<GraphicsSystem>(this, map);
	systemManager.add<InputSystem>(keyboardManager, mouseManager);

	systemManager.configure();
}