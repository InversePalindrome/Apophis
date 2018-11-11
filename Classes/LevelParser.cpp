/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelParser.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "LevelParser.hpp"
#include "EntityParser.hpp"

#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


void LevelParser::parseLevel(std::unordered_map<std::string, entityx::Entity>& entities, b2Vec2& mapDimensions, entityx::EntityManager& entityManager, entityx::EventManager& eventManager, const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
	{
		if (const auto levelNode = doc.child("Level"))
		{
			if (const auto widthAttribute = levelNode.attribute("width"))
			{
				mapDimensions.x = widthAttribute.as_float();
			}
			if (const auto heightAttribute = levelNode.attribute("height"))
			{
				mapDimensions.y = heightAttribute.as_float();
			}

			for (const auto entityNode : levelNode.children("Entity"))
			{
				std::string entityName;
				auto entity = entityManager.create();
				
				EntityParser::parseName(entityName, entity, entityNode);
				EntityParser::parseEntity(entity, eventManager, entityNode);
				
				entities.emplace(entityName, entity);

				eventManager.emit(EntityParsed{ entity });
			}
		}
	}
}