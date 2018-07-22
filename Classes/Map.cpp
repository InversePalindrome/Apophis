/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.cpp
InversePalindrome.com
*/


#include "Map.hpp"
#include "Constants.hpp"

#include <cocos/2d/CCSprite.h>
#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


Map::Map() :
	dimensions(0.f, 0.f)
{
}

void Map::init(cocos2d::Node* gameNode)
{
	this->gameNode = gameNode;
}

void Map::load(const std::string& fileName)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName + ".xml").c_str()))
	{
		if (const auto mapNode = doc.child("Map"))
		{
			if (const auto widthAttribute = mapNode.attribute("width"))
			{
				dimensions.x = widthAttribute.as_float();
			}
			if (const auto heightAttribute = mapNode.attribute("height"))
			{
				dimensions.y = heightAttribute.as_float();
			}
			if (const auto backgroundAttribute = mapNode.attribute("background"))
			{
				auto* sprite = cocos2d::Sprite::createWithSpriteFrameName(backgroundAttribute.as_string());
				sprite->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
				sprite->setTextureRect({ 0.f, 0.f, dimensions.x * Constants::PTM_RATIO, dimensions.y * Constants::PTM_RATIO });

				gameNode->addChild(sprite);
			}
		}
	}
}

b2Vec2 Map::getDimensions() const
{
	return dimensions;
}