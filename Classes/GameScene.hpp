/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <cocos/2d/CCScene.h>

#include <Box2D/Common/b2Math.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>


class GameScene : public cocos2d::Scene, public entityx::Receiver<GameScene>
{
public:
	explicit GameScene(const std::string& level);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void receive(const EntityDied& event);

	static GameScene* create();

private:
	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	std::string level;
	b2Vec2 mapDimensions;

	void initSystems();
	void reloadGame();
};