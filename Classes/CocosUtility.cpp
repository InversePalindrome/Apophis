/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CocosUtility.cpp
InversePalindrome.com
*/


#include "CocosUtility.hpp"

#include <cocos/platform/CCFileUtils.h>
#include <cocos/2d/CCSpriteFrameCache.h>

#include <pugixml.hpp>


void CocosUtility::createSearchPaths(const std::string& filename)
{
	auto* files = cocos2d::FileUtils::getInstance();
	
	if (pugi::xml_document doc; doc.load_file(files->fullPathForFilename(filename + ".xml").c_str()))
	{
		if (const auto searchPathsNode = doc.child("SearchPaths"))
		{
			for (const auto searchPathNode : searchPathsNode.children())
			{
				files->addSearchPath(searchPathNode.name());
			}
		}
	}
}

void CocosUtility::initSpriteFrames(const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename + ".xml").c_str()))
	{
		if (const auto spritesNode = doc.child("SpriteFrames"))
		{
			for (const auto spriteNode : spritesNode.children())
			{
				cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(std::string(spriteNode.name()) + ".plist");
			}
		}
	}
}