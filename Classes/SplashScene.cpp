/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SplashScene.cpp
InversePalindrome.com
*/


#include "StartScene.hpp"
#include "SplashScene.hpp"

#include <CreatorReader.h>

#include <cocos/base/CCDirector.h>


cocos2d::Scene* getSplashScene()
{
	auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Splash.ccreator");
	reader->setup();

	auto* scene = reader->getSceneGraph();

	scene->scheduleOnce([](float dt) { cocos2d::Director::getInstance()->replaceScene(getStartScene()); }, 2.f, "Splash");

	return scene;
}