/*
Copyright (c) 2018 Inverse Palindrome
Apophis - MenuScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "SettingsScene.hpp"
#include "LevelEditorNode.hpp"
#include "LevelSelectionScene.hpp"

#include <CreatorReader.h>

#include <cocos/ui/UIButton.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>


cocos2d::Scene* getMenuScene()
{
    auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Menu.ccreator");
    reader->setup();

    auto* scene = reader->getSceneGraph();
    auto* canvas = scene->getChildByName("Canvas");
    auto* director = cocos2d::Director::getInstance();

    static_cast<cocos2d::ui::Button*>(canvas->getChildByName("playButton"))->addTouchEventListener([director](auto * sender, auto event)
        {
            director->replaceScene(getLevelSelectionScene());
        });
    static_cast<cocos2d::ui::Button*>(canvas->getChildByName("settingsButton"))->addTouchEventListener([director](auto * sender, auto event)
        {
            director->pushScene(getSettingsScene());
        });
    static_cast<cocos2d::ui::Button*>(canvas->getChildByName("exitButton"))->addTouchEventListener([director](auto * sender, auto event)
        {
            director->end();
        });

    auto* keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [director](const auto keyCode, auto * event)
    {
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_L)
        {
            director->replaceScene(LevelEditorNode::scene());
        }
    };

    canvas->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, canvas);

    return scene;
}