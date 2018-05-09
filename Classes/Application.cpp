/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - Application.cpp
InversePalindrome.com
*/


#include "SplashNode.hpp"
#include "Application.hpp"
#include "AudioManager.hpp"

#include <tinyxml2/tinyxml2.h>

#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/2d/CCSpriteFrameCache.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>


bool Application::applicationDidFinishLaunching()
{
	auto* director = cocos2d::Director::getInstance();
	auto* view = director->getOpenGLView();

	if (!view)
	{
		view = cocos2d::GLViewImpl::create("JATR66");
		view->setFrameSize(2048.f, 1536.f);
     	view->setDesignResolutionSize(2048.f, 1536.f, ResolutionPolicy::EXACT_FIT);
	
		director->setOpenGLView(view);
		director->setClearColor(cocos2d::Color4F::WHITE);
	}

	createSearchPaths();

	initSpriteFrames();

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

void Application::createSearchPaths()
{
	auto* files = cocos2d::FileUtils::getInstance();

	files->addSearchPath(files->getWritablePath());
	files->addSearchPath("Fonts/");
	files->addSearchPath("Sprites/");
	files->addSearchPath("Sounds/");
	files->addSearchPath("Music/");
	files->addSearchPath("Entities/");
	files->addSearchPath("Particles/");
	files->addSearchPath("Maps/");
}

void Application::initSpriteFrames()
{
	auto* files = cocos2d::FileUtils::getInstance();
	const auto& path = files->fullPathForFilename("SpriteFrames.xml");
	const auto& data = files->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* resourcesNode = doc.RootElement())
	{
		for (const auto* resourceNode = resourcesNode->FirstChildElement("Sprite"); resourceNode; resourceNode = resourceNode->NextSiblingElement("Sprite"))
		{
			cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(std::string(resourceNode->GetText()) + ".plist");
		}
	}
}