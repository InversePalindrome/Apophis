/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>

#include <vector>


class LevelEditorNode: public cocos2d::Node, public entityx::Receiver<LevelEditorNode>
{
public:
	LevelEditorNode();

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void receive(const entityx::EntityCreatedEvent& event);
	virtual void receive(const entityx::EntityDestroyedEvent& event);

	CREATE_FUNC(LevelEditorNode);

	static cocos2d::Scene* scene();

private:
	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;
	
	std::vector<entityx::Entity> entities;

	void initSystems();
};