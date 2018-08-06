/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorScene.hpp
InversePalindrome.com
*/


#pragma once

#include "fairygui/GRoot.h"

#include <cocos/2d/CCScene.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>


class LevelEditorScene : public cocos2d::Scene
{
public:
	LevelEditorScene();
	~LevelEditorScene();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(LevelEditorScene);

private:
	entityx::EventManager eventManager;
	entityx::EntityManager entityManager;
	entityx::SystemManager systemManager;

	fairygui::GRoot* gui;

	fairygui::GComponent* view;

	void initSystems();
};