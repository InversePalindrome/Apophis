/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "EntityParser.hpp"
#include "ComponentParser.hpp"

#include <cocos/platform/CCFileUtils.h>

#include <brigand/algorithms/for_each.hpp>


void EntityParser::parseEntity(entityx::Entity& entity, entityx::EventManager& eventManager, const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
	{
		if (const auto entityNode = doc.child("Entity"))
		{
			parseEntity(entity, eventManager, entityNode);
		}
	}
}

void EntityParser::parseEntity(entityx::Entity& entity, entityx::EventManager& eventManager, const pugi::xml_node& entityNode)
{
	for (const auto componentNode : entityNode.children())
	{
		if (componentParser.count(componentNode.name()))
		{
			std::visit([entity, &eventManager, &componentNode](auto& component)
			{ 
				component->load(componentNode);
			
				eventManager.emit(ComponentLoaded<std::decay_t<decltype(component)>>{ component, entity });
			}, componentParser.at(componentNode.name())(entity));
		}
	}

	eventManager.emit(EntityParsed{ entity });
	eventManager.emit(UpdateTransform{ entity });
}