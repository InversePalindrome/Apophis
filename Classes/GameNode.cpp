/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameNode.cpp
InversePalindrome.com
*/


#include "GameNode.hpp"
#include "ItemSystem.hpp"
#include "LevelParser.hpp"
#include "StateSystem.hpp"
#include "AudioSystem.hpp"
#include "DroneSystem.hpp"
#include "ActionSystem.hpp"
#include "PlayerSystem.hpp"
#include "CombatSystem.hpp"
#include "CameraSystem.hpp"
#include "PatrolSystem.hpp"
#include "PhysicsSystem.hpp"
#include "OrbitalSystem.hpp"
#include "StrikerSystem.hpp"
#include "GraphicsSystem.hpp"
#include "ObjectComponent.hpp"

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>
#include <cocos/base/CCEventListenerKeyboard.h>


GameNode::GameNode(const std::string& level) :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	level(level),
	mapDimensions(0.f, 0.f)
{
}

bool GameNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	auto* keyboardListener = cocos2d::EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [this](const auto keyCode, auto* event)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			unscheduleUpdate();

			getEventDispatcher()->dispatchCustomEvent("pause");
		}
	};

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("resume", [this](auto* event) { scheduleUpdate(); }), this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("retry", [this](auto* event) { reloadGame(); }), this);

	initSystems();

	reloadGame();

	return true;
}

void GameNode::update(float dt)
{
	systemManager.update_all(dt);
}

void GameNode::receive(const EntityDied& event)
{
	auto entity = event.entity;
	
	if (const auto object = entity.component<ObjectComponent>(); object && object->getObjectType() == +ObjectType::Player)
	{
		unscheduleUpdate();

		getEventDispatcher()->dispatchCustomEvent("gameOver");
	}
}

GameNode* GameNode::create(const std::string& level)
{
	auto* gameNode = new(std::nothrow)GameNode(level);

	if (gameNode && gameNode->init())
	{
		gameNode->autorelease();
		return gameNode;
	}

	delete gameNode;
	gameNode = nullptr;

	return nullptr;
}

void GameNode::initSystems()
{
	systemManager.add<DroneSystem>(entityManager, eventManager);
	systemManager.add<StrikerSystem>(eventManager);
	systemManager.add<PlayerSystem>(this);
	systemManager.add<PatrolSystem>();
	systemManager.add<StateSystem>(eventManager);
	systemManager.add<ActionSystem>();
	systemManager.add<CameraSystem>(this, mapDimensions);
	systemManager.add<AudioSystem>();
	systemManager.add<OrbitalSystem>();
	systemManager.add<ItemSystem>(entityManager, eventManager);
	systemManager.add<PhysicsSystem>(entityManager, eventManager);
	systemManager.add<CombatSystem>(entityManager, eventManager);
	systemManager.add<GraphicsSystem>(this);
	
	eventManager.subscribe<EntityDied>(*this);
	
	systemManager.configure();
}

void GameNode::reloadGame()
{
	scheduleUpdate();

	entityManager.reset();

	LevelParser::parseLevel(entityManager, eventManager, mapDimensions, level);
}