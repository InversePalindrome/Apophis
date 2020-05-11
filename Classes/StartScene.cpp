/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StartScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "StartScene.hpp"
#include "AppSettings.hpp"

#include <CreatorReader.h>

#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventListenerKeyboard.h>


cocos2d::Scene* getStartScene()
{
    auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Start.ccreator");
    reader->setup();

    auto* scene = reader->getSceneGraph();

    auto* keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [](const auto keyCode, auto* event)
    {
        cocos2d::Director::getInstance()->replaceScene(getMenuScene());
    };

    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, scene);

    AppSettings::getInstance().playMusic("LightYearsMusic.mp3", true);

    return scene;
}