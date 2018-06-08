/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CocosUtility.cpp
InversePalindrome.com
*/


#include "CocosUtility.hpp"

#include <tinyxml2/tinyxml2.h>

#include <cocos/platform/CCFileUtils.h>
#include <cocos/2d/CCSpriteFrameCache.h>


void CocosUtility::createSearchPaths(const std::string& filename)
{
    auto* files = cocos2d::FileUtils::getInstance();
	auto path = files->fullPathForFilename(filename + ".xml");
	auto data = files->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* searchPathsNode = doc.RootElement())
	{
		for (const auto* searchPathNode = searchPathsNode->FirstChildElement(); searchPathNode; searchPathNode = searchPathNode->NextSiblingElement())
		{
			files->addSearchPath(searchPathNode->Value());
		}
	}
}

void CocosUtility::initSpriteFrames(const std::string& filename)
{
	auto* files = cocos2d::FileUtils::getInstance();
	auto path = files->fullPathForFilename(filename + ".xml");
	auto data = files->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* resourcesNode = doc.RootElement())
	{
		for (const auto* resourceNode = resourcesNode->FirstChildElement(); resourceNode; resourceNode = resourceNode->NextSiblingElement())
		{
			cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(std::string(resourceNode->Value()) + ".plist");
		}
	}
}