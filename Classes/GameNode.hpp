/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameNode.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Events.hpp"
#include "MouseManager.hpp"
#include "EntityParser.hpp"
#include "KeyboardManager.hpp"

#include <entityx/entityx.h>

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class GameNode : public cocos2d::Node
{
public:
	GameNode();
	~GameNode();

	virtual bool init() override;
	virtual void update(float dt) override;
	
	CREATE_FUNC(GameNode);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	EntityParser entityParser;

	Map map;

	void initSystems();
};