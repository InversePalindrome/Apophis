/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ResourceParser.cpp
InversePalindrome.com
*/


#include "ResourceParser.hpp"

#include <cocos/2d/CCAnimationCache.h>
#include <cocos/platform/CCFileUtils.h>
#include <cocos/2d/CCSpriteFrameCache.h>

#include <pugixml.hpp>


void ResourceParser::parseResources(const std::string& filename)
{
    if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
    {
        if (const auto resourcesNode = doc.child("Resources"))
        {
            for (const auto spriteSheetNode : resourcesNode.children("SpriteSheet"))
            {
                cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteSheetNode.text().as_string());
            }
            for (const auto animationNode : resourcesNode.children("AnimationSheet"))
            {
                cocos2d::AnimationCache::getInstance()->addAnimationsWithFile(animationNode.text().as_string());
            }
        }
    }
}