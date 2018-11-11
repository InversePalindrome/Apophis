/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.hpp
InversePalindrome.com
*/


#pragma once

#include "PanZoomLayer.h"

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>

#include <Box2D/Common/b2Math.h>

#include <unordered_map>


class LevelEditorNode: public PanZoomLayer, public entityx::Receiver<LevelEditorNode>
{
public:
	LevelEditorNode();

	virtual bool init() override;

	CREATE_FUNC(LevelEditorNode);

	static cocos2d::Scene* scene();

private:
	std::unordered_map<std::string, entityx::Entity> entities;

	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;
	
	std::string entityName;
	b2Vec2 mapDimensions;

	void initSystems();
};