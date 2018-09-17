/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "AppSettings.hpp"
#include "SplashScene.hpp"
#include "LevelManager.hpp"
#include "ResourceParser.hpp"

#include "CCIMGUIGLViewImpl.h"

#include <imgui.h>

#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/audio/include/AudioEngine.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>


Application::~Application()
{
	AppSettings::getInstance().save(cocos2d::FileUtils::getInstance()->getWritablePath() + "Settings.xml");
	LevelManager::getInstance().save(cocos2d::FileUtils::getInstance()->getWritablePath() + "Levels.xml");

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
	files->addSearchPath("Entities");
	files->addSearchPath("Sprites");
	files->addSearchPath("Animations");
	files->addSearchPath("Particles");
	files->addSearchPath("Fonts");
	files->addSearchPath("Sounds");
	files->addSearchPath(cocos2d::FileUtils::getInstance()->getWritablePath());
	
	ResourceParser::parseResources("Resources.xml");
	ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/OpenSans-Regular.ttf", 40.f);

	AppSettings::getInstance().load("Settings.xml");
	LevelManager::getInstance().load("Levels.xml");

	director->runWithScene(getSplashScene());

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