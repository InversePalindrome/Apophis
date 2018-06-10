/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.cpp
InversePalindrome.com
*/


#include "Map.hpp"
#include "Events.hpp"
#include "Constants.hpp"

#include <cocos/2d/CCSprite.h>
#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>

#include <boost/math/constants/constants.hpp>


Map::Map(EntityParser& entityParser, entityx::EventManager& eventManager) :
	entityParser(entityParser),
	eventManager(eventManager),
	maxEntityCount(0u)
{
}

void Map::load(const std::string& fileName)
{
    pugi::xml_document doc;

	if (doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName + ".xml").c_str()))
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

				mainNode->addChild(sprite);
			}
			if (const auto maxEntityCountAttribute = mapNode.attribute("maxEntityCount"))
			{
				maxEntityCount = maxEntityCountAttribute.as_ullong();
			}
			for (const auto entitiesNode : mapNode.children("Entities"))
			{
				for (const auto entityNode : entitiesNode.children())
				{
					std::vector<std::string> entities;
					std::vector<int> weights;

					for (const auto entityNode : entitiesNode.children())
					{
						entities.push_back(entityNode.name());
						weights.push_back(entityNode.text().as_int());
					}

					generateMap(entities, weights);
				}
			}
		}
	}
}

void Map::setMainNode(cocos2d::Node* mainNode)
{
	this->mainNode = mainNode;
}

b2Vec2 Map::getDimensions() const
{
	return dimensions;
}

void Map::generateMap(const std::vector<std::string>& entities, const std::vector<int>& weights)
{
	std::random_device rd;
	std::mt19937 randomEngine(rd());
	std::discrete_distribution<> distribution(std::cbegin(weights), std::cend(weights));

	for (std::size_t i = 0; i < maxEntityCount; ++i)
	{ 
		//auto entity = entityParser.createEntity(entities.at(distribution(randomEngine)));


	}
}