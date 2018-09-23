/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameScene.cpp
InversePalindrome.com
*/


#include "HudNode.hpp"
#include "GameScene.hpp"
#include "ItemSystem.hpp"
#include "LevelParser.hpp"
#include "StateSystem.hpp"
#include "AudioSystem.hpp"
#include "ActionSystem.hpp"
#include "PlayerSystem.hpp"
#include "CombatSystem.hpp"
#include "CameraSystem.hpp"
#include "PhysicsSystem.hpp"
#include "OrbitalSystem.hpp"
#include "StrikerSystem.hpp"
#include "TagsComponent.hpp"
#include "GraphicsSystem.hpp"

#include <CreatorReader.h>

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerCustom.h>
#include <cocos/base/CCEventListenerKeyboard.h>


GameScene::GameScene(const std::string& level) :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	level(level),
	mapDimensions(0.f, 0.f)
{
}

bool GameScene::init()
{
	if (!Scene::init())
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
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("playAgain", [this](auto* event) { reloadGame(); }), this);

	scheduleUpdate();
	initSystems();
   
	LevelParser::parseLevel(entityManager, eventManager, mapDimensions, "Level.xml");
	
	return true;
}

void GameScene::update(float dt)
{
	systemManager.update_all(dt);
}

void GameScene::receive(const EntityDied& event)
{
	auto entity = event.entity;
	
	if (const auto tags = entity.component<TagsComponent>(); tags && tags->hasTag("Player"))
	{
		unscheduleUpdate();
		getEventDispatcher()->dispatchCustomEvent("gameOver");
	}
}

GameScene* GameScene::create()
{
	auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Game.ccreator");
	reader->setup();

	auto* scene = static_cast<GameScene*>(reader->getSceneGraph());

	if (scene && scene->init())
	{
		scene->autorelease();

		auto* canvas = scene->getChildByName("Canvas");
		auto* director = cocos2d::Director::getInstance();

		return scene;
	}

	scene = nullptr;
	return nullptr;
}

void GameScene::initSystems()
{
	systemManager.add<StrikerSystem>();
	systemManager.add<PlayerSystem>(this);
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

void GameScene::reloadGame()
{
	scheduleUpdate();

	eventManager.emit(GameReset{});

	entityManager.reset();

	LevelParser::parseLevel(entityManager, eventManager, mapDimensions, level);
}