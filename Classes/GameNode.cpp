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
#include "ActionSystem.hpp"
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
#include <cocos/base/CCEventListenerKeyboard.h>

#include <entityx/deps/Dependencies.h>


GameNode::GameNode() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	entityParser(entityManager, eventManager),
	map(entityParser, eventManager)
{
}

bool GameNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	scheduleUpdate();

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("resume", [this](auto* event) { scheduleUpdate(); }), this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("gameOver", [this](auto* event){ entityManager.reset(); }), this);

	auto* keyboardListener = cocos2d::EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [this](const auto keyCode, auto* event)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			unscheduleUpdate();
			getEventDispatcher()->dispatchCustomEvent("pause");
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	map.setMainNode(this);
	
	initSystems();

	map.load("Andromeda");
	entityParser.createEntity("UFO");
	entityParser.createEntity("Planet");
	entityParser.createEntity("SpaceCruiser");
	entityParser.createEntity("Billboard");
	auto coin = entityParser.createEntity("Coin");
	eventManager.emit(PlayAnimation{ coin, Animation::Alert, true });
	//auto asteroid = entityParser.createEntity("BlueAsteroid");

   // eventManager.emit(CreateDistanceJoint{ planet, asteroid });

	return true;
}

void GameNode::update(float dt)
{
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
	systemManager.add<PlayerSystem>(this);
	systemManager.add<AudioSystem>();
	systemManager.add<ActionSystem>();
	systemManager.add<OrbitalSystem>();
	systemManager.add<ItemSystem>(entityParser);
	systemManager.add<PhysicsSystem>(entityManager, eventManager);
	systemManager.add<CombatSystem>(entityParser);
	systemManager.add<GraphicsSystem>(this, map);
	systemManager.add<entityx::deps::Dependency<SpeedComponent, ImpulseComponent>>();
	
	systemManager.configure();
}