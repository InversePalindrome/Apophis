/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSelectionScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "LevelSelectionScene.hpp"

#include <CreatorReader.h>

#include <cocos/ui/UIButton.h>
#include <cocos/base/CCDirector.h>


cocos2d::Scene* getLevelSelectionScene()
{
	auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/LevelSelection.ccreator");
	reader->setup();

	auto* scene = reader->getSceneGraph();
	auto* canvas = scene->getChildByName("Canvas");
	auto* director = cocos2d::Director::getInstance();

	static_cast<cocos2d::ui::Button*>(canvas->getChildByName("backButton"))->addTouchEventListener([director](auto* sender, auto event) 
	{ 
		director->replaceScene(getMenuScene());
	});

	return scene;
}