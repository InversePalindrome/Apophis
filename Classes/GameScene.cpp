/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameScene.cpp
InversePalindrome.com
*/


#include "MenuNode.hpp"
#include "AISystem.hpp"
#include "GameScene.hpp"
#include "ItemSystem.hpp"
#include "InputSystem.hpp"
#include "AudioSystem.hpp"
#include "SettingsNode.hpp"
#include "CombatSystem.hpp"
#include "ControlSystem.hpp"
#include "PhysicsSystem.hpp"
#include "EntityFactory.hpp"
#include "SteeringSystem.hpp"
#include "GraphicsSystem.hpp"
#include "SatelliteSystem.hpp"
#include "SchedulingSystem.hpp"

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
	gameNode->release();
	hudNode->release();
	pauseNode->release();
}

bool GameScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	scheduleUpdate();

	keyboardManager = KeyboardManager::create();
	keyboardManager->retain();

	mouseManager = MouseManager::create();
	mouseManager->retain();

	gameNode = cocos2d::Node::create();
	gameNode->addChild(keyboardManager);
	gameNode->addChild(mouseManager);
	gameNode->retain();

	hudNode = HudNode::create();
	hudNode->retain();

	pauseNode = PauseNode::create();
	pauseNode->retain();

	addChild(gameNode);
	addChild(hudNode);
	addChild(pauseNode);

	map.setMainNode(gameNode);
	
	initSystems();

	map.load("Andromeda");
	entityFactory.createEntities("LevelEntities");

	return true;
}

void GameScene::update(float dt)
{
	if (keyboardManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		unscheduleUpdate();
		pauseNode->setVisible(true);
	}
	
	systemManager.update_all(dt);
}

void GameScene::initSystems()
{
	systemManager.add<ControlSystem>(entityFactory);
	systemManager.add<AISystem>();
	systemManager.add<AudioSystem>();
	systemManager.add<SteeringSystem>();
	systemManager.add<SchedulingSystem>();
	systemManager.add<SatelliteSystem>();
	systemManager.add<ItemSystem>(entityFactory);
	systemManager.add<PhysicsSystem>(eventManager);
	systemManager.add<CombatSystem>(entityFactory);
	systemManager.add<GraphicsSystem>(gameNode, hudNode, map);
	systemManager.add<InputSystem>(keyboardManager, mouseManager);
	
	systemManager.configure();
}