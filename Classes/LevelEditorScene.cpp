/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorScene.cpp
InversePalindrome.com
*/


#include "ActionSystem.hpp"
#include "GraphicsSystem.hpp"
#include "LevelSerializer.hpp"
#include "LevelEditorScene.hpp"

#include <fairygui/UIPackage.h>


LevelEditorScene::LevelEditorScene() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager)
{
}

LevelEditorScene::~LevelEditorScene()
{
	gui->release();
}

bool LevelEditorScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	scheduleUpdate();
	initSystems();

	gui = fairygui::GRoot::create(this);
	gui->retain();

	fairygui::UIPackage::addPackage("GUI/EntityCreator");
	auto* button = fairygui::UIPackage::createObject("EntityCreator", "View");

	gui->addChild(button);

	return true;
}

void LevelEditorScene::update(float dt)
{
	systemManager.update_all(dt);
}

void LevelEditorScene::initSystems()
{
	systemManager.add<ActionSystem>();

	systemManager.configure();
}