/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Application.cpp
InversePalindrome.com
*/


#include "SplashNode.hpp"
#include "Application.hpp"
#include "CocosUtility.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>


bool Application::applicationDidFinishLaunching()
{
	auto* director = cocos2d::Director::getInstance();

	if (auto* view = director->getOpenGLView(); !view)
	{
		view = cocos2d::GLViewImpl::create("Apophis");
		view->setFrameSize(2048.f, 1536.f);
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
}

void Application::applicationWillEnterForeground()
{
	cocos2d::Director::getInstance()->startAnimation();
}