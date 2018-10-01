/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSelectionScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "LevelManager.hpp"
#include "LevelSelectionScene.hpp"

#include <CreatorReader.h>

#include <cocos/ui/UIButton.h>
#include <cocos/ui/UIPageView.h>
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
	/*
	auto* levelsPageView = static_cast<cocos2d::ui::PageView*>(canvas->getChildByName("levelsPageView"));
	auto* levelsView = levelsPageView->getChildByName("levelsView");
	auto* levelsPages = levelsView->getChildByName("levelsPages");

	auto levelIndex = 0u;

	for(auto* levelPage : levelsPageView->getPages())
	{
		for (auto* levelButton : levelPage->getChildren())
		{
			static_cast<cocos2d::ui::Button*>(levelButton)->addTouchEventListener([director, levelIndex](auto* sender, auto event)
			{
				director->replaceScene(getGameScene(LevelManager::getInstance()[levelIndex]));
			});
		}
	}*/
	
	auto* button = cocos2d::ui::Button::create("RegularRectangleButton", "SelectedRectangleButton", "", cocos2d::ui::Widget::TextureResType::PLIST);
	button->setPosition({ 300.f, 300.f });
	canvas->addChild(button);
	button->addTouchEventListener([director](auto* sender, auto event)
	{
		director->replaceScene(getGameScene("MilkyWay.xml"));
	});
	
	return scene;
}