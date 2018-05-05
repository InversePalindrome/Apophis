/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - GameScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Events.hpp"
#include "MouseManager.hpp"
#include "EntityFactory.hpp"
#include "KeyboardManager.hpp"

#include <entityx/entityx.h>

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCScene.h>


class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

	virtual bool init() override;
	virtual void update(float dt) override;
	
	CREATE_FUNC(GameScene);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	EntityFactory entityFactory;

	Map map;

	cocos2d::Layer* createPauseMenu();

	void initSystems();
};