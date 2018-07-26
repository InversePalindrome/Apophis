/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameNode.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Events.hpp"
#include "EntityFactory.hpp"
#include "EntitySerializer.hpp"

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>


class GameNode : public cocos2d::Node, public entityx::Receiver<GameNode>
{
public:
	GameNode();

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	
	CREATE_FUNC(GameNode);

	static cocos2d::Scene* scene();

private:
	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	EntityFactory entityFactory;
	EntitySerializer entitySerializer;

	Map map;

	void initSystems();
};