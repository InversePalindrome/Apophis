/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Application.cpp
InversePalindrome.com
*/


#include "SplashNode.hpp"
#include "Application.hpp"
#include "CocosUtility.hpp"

#include "CCIMGUIGLViewImpl.h"

#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/audio/include/AudioEngine.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>


Application::~Application()
{
	cocos2d::experimental::AudioEngine::end();
}

bool Application::applicationDidFinishLaunching()
{
	auto* director = cocos2d::Director::getInstance();

	if (auto* view = director->getOpenGLView(); !view)
	{
		view = cocos2d::IMGUIGLViewImpl::createWithRect("Apophis", { 0, 0, 2048, 1536 });
		view->setDesignResolutionSize(2048.f, 1536.f, ResolutionPolicy::EXACT_FIT);

		director->setOpenGLView(view);
		director->setClearColor(cocos2d::Color4F::WHITE);
	}

	auto* files = cocos2d::FileUtils::getInstance();
	files->addSearchPath(files->getWritablePath());

	CocosUtility::createSearchPaths("SearchPaths");
	CocosUtility::initSpriteFrames("SpriteFrames");

	director->runWithScene(SplashNode::scene());

	return true;
}

void Application::applicationDidEnterBackground()
{
	cocos2d::Director::getInstance()->stopAnimation();
    cocos2d::experimental::AudioEngine::pauseAll();
}

void Application::applicationWillEnterForeground()
{
	cocos2d::Director::getInstance()->startAnimation();
	cocos2d::experimental::AudioEngine::resumeAll();
}