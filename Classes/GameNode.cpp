/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameNode.cpp
InversePalindrome.com
*/


#include "HudNode.hpp"
#include "MenuNode.hpp"
#include "GameNode.hpp"
#include "PauseNode.hpp"
#include "ItemSystem.hpp"
#include "AudioSystem.hpp"
#include "PlayerSystem.hpp"
#include "SettingsNode.hpp"
#include "CombatSystem.hpp"
#include "GameOverNode.hpp"
#include "PhysicsSystem.hpp"
#include "OrbitalSystem.hpp"
#include "StrikerSystem.hpp"
#include "GraphicsSystem.hpp"
#include "ImpulseComponent.hpp"

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>

#include <entityx/deps/Dependencies.h>


GameNode::GameNode() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	entityParser(entityManager, eventManager),
	map(entityParser, eventManager)
{
}

GameNode::~GameNode()
{
	keyboardManager->release();
	mouseManager->release();
}

bool GameNode::init()
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

	addChild(keyboardManager);
	addChild(mouseManager);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("resume", [this](auto* event) { scheduleUpdate(); }), this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("gameOver", [this](auto* event)
	{
		entityManager.reset();
	}), this);

	map.setMainNode(this);
	
	initSystems();

	map.load("Andromeda");
	entityParser.createEntity("UFO");
	entityParser.createEntity("SpaceCruiser");
	auto planet = entityParser.createEntity("Planet");
	//auto asteroid = entityParser.createEntity("BlueAsteroid");

   // eventManager.emit(CreateDistanceJoint{ planet, asteroid });

	return true;
}

void GameNode::update(float dt)
{
	if (keyboardManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		unscheduleUpdate();
		getEventDispatcher()->dispatchCustomEvent("pause");
	}
	
	systemManager.update_all(dt);
}

cocos2d::Scene* GameNode::scene()
{
	auto* scene = cocos2d::Scene::create();

	scene->addChild(GameNode::create());
	scene->addChild(HudNode::create());
	scene->addChild(PauseNode::create());
	scene->addChild(GameOverNode::create());

	return scene;
}

void GameNode::initSystems()
{
	systemManager.add<StrikerSystem>();
	systemManager.add<PlayerSystem>(keyboardManager, mouseManager);
	systemManager.add<AudioSystem>();
	systemManager.add<OrbitalSystem>();
	systemManager.add<ItemSystem>(entityParser);
	systemManager.add<PhysicsSystem>(entityManager, eventManager);
	systemManager.add<CombatSystem>(entityParser);
	systemManager.add<GraphicsSystem>(this, map);
	systemManager.add<entityx::deps::Dependency<SpeedComponent, ImpulseComponent>>();

	systemManager.configure();
}