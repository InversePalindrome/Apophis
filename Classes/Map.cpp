/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.cpp
InversePalindrome.com
*/


#include "Map.hpp"
#include "Events.hpp"
#include "Constants.hpp"

#include <tinyxml2/tinyxml2.h>

#include <cocos/2d/CCSprite.h>
#include <cocos/platform/CCFileUtils.h>


Map::Map(EntityParser& entityParser, entityx::EventManager& eventManager) :
	entityParser(entityParser),
	eventManager(eventManager),
	maxEntityCount(0u)
{
}

void Map::load(const std::string& fileName)
{
	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(fileName + ".xml");
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* mapNode = doc.RootElement())
	{
		const auto* width = mapNode->Attribute("width");
		const auto* height = mapNode->Attribute("height");

		if (width && height)
		{
			dimensions = { std::stof(width), std::stof(height) };
		}
		if (const auto* background = mapNode->Attribute("background"))
		{
			auto* sprite = cocos2d::Sprite::createWithSpriteFrameName(background);
			sprite->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
			sprite->setTextureRect({ 0.f, 0.f, dimensions.x * Constants::PTM_RATIO, dimensions.y * Constants::PTM_RATIO });

			mainNode->addChild(sprite);
		}
		if (const auto* maxEntityCount = mapNode->Attribute("maxEntityCount"))
		{
			this->maxEntityCount = std::stoull(maxEntityCount);
		}
		if (const auto* entitiesNode = mapNode->FirstChildElement("Entities"))
		{
			std::vector<std::string> entities;
			std::vector<int> weights;

			for (const auto* entityNode = entitiesNode->FirstChildElement(); entityNode; entityNode = entityNode->NextSiblingElement())
			{
				entities.push_back(entityNode->Value());
				weights.push_back(std::stoi(entityNode->GetText()));
			}

			generateMap(entities, weights);
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
		/*
		auto entity = entityParser.createEntity(entities.at(distribution(randomEngine)));

		eventManager.emit(SetPosition{ entity, { cocos2d::rand_minus1_1() * dimensions.x / 2.f, cocos2d::rand_minus1_1() * dimensions.y / 2.f } });
		eventManager.emit(SetRotation{ entity, cocos2d::RandomHelper::random_real(0.f, 2.f * PI) });*/
	}
}