/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameScene.cpp
InversePalindrome.com
*/


#include "GameNode.hpp"
#include "GameScene.hpp"
#include "AppSettings.hpp"
#include "SettingsScene.hpp"
#include "LevelSelectionScene.hpp"

#include <CreatorReader.h>

#include <cocos/base/CCDirector.h>


cocos2d::Scene* getGameScene(const std::string& level)
{
	auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Game.ccreator");
    reader->setup();

    auto* scene = reader->getSceneGraph();
    auto* canvas = scene->getChildByName("Canvas");
    auto* director = cocos2d::Director::getInstance();

	scene->setOnEnterCallback([]() { AppSettings::getInstance().stopMusic(); });
	scene->setOnExitCallback([]() { AppSettings::getInstance().playMusic("LightYearsMusic.mp3", true); });

	canvas->addChild(GameNode::create(level));

	auto* pauseNode = canvas->getChildByName("pauseNode");
	pauseNode->setLocalZOrder(1);
	pauseNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("pause", [pauseNode](auto* event) { pauseNode->setVisible(true); }), canvas);

	static_cast<cocos2d::ui::Button*>(pauseNode->getChildByName("resumeButton"))->addTouchEventListener([scene, pauseNode](auto* sender, auto event)
	{
		pauseNode->setVisible(false);

		scene->getEventDispatcher()->dispatchCustomEvent("resume");
	});
	static_cast<cocos2d::ui::Button*>(pauseNode->getChildByName("retryButton"))->addTouchEventListener([scene, pauseNode](auto* sender, auto event)
	{
		pauseNode->setVisible(false);

		scene->getEventDispatcher()->dispatchCustomEvent("retry");
	});
	static_cast<cocos2d::ui::Button*>(pauseNode->getChildByName("settingsButton"))->addTouchEventListener([director](auto* sender, auto event)
	{
		director->pushScene(getSettingsScene());
	});
	static_cast<cocos2d::ui::Button*>(pauseNode->getChildByName("quitButton"))->addTouchEventListener([director](auto* sender, auto event)
	{
		director->replaceScene(getLevelSelectionScene());
	});
	
	auto* gameOverNode = canvas->getChildByName("gameOverNode");
	gameOverNode->setLocalZOrder(1);
	gameOverNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create("gameOver", [gameOverNode](auto* event) { gameOverNode->setVisible(true); }), canvas);

	static_cast<cocos2d::ui::Button*>(gameOverNode->getChildByName("retryButton"))->addTouchEventListener([scene, gameOverNode](auto* sender, auto event)
	{
		gameOverNode->setVisible(false);

		scene->getEventDispatcher()->dispatchCustomEvent("retry");
	});
	static_cast<cocos2d::ui::Button*>(gameOverNode->getChildByName("settingsButton"))->addTouchEventListener([director](auto* sender, auto event)
	{
		director->pushScene(getSettingsScene());
	});
	static_cast<cocos2d::ui::Button*>(gameOverNode->getChildByName("quitButton"))->addTouchEventListener([director](auto* sender, auto event)
	{
		director->replaceScene(getLevelSelectionScene());
	});

    return scene;
}