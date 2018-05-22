/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Events.hpp"
#include "HudNode.hpp"
#include "PauseNode.hpp"
#include "MouseManager.hpp"
#include "EntityParser.hpp"
#include "KeyboardManager.hpp"

#include <entityx/entityx.h>

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init() override;
	virtual void update(float dt) override;
	
	CREATE_FUNC(GameScene);

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	cocos2d::Node* gameNode;
	HudNode* hudNode;
	PauseNode* pauseNode;

	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	EntityParser entityParser;

	Map map;

	void initSystems();
};