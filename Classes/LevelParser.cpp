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


void LevelParser::parseLevel(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, b2Vec2& mapDimensions, const std::string& filename)
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
                auto entity = entityManager.create();

                EntityParser::parseEntity(entity, eventManager, entityNode);

                eventManager.emit(EntityParsed{ entity });
            }
        }
    }
}