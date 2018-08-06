/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSerializer.cpp
InversePalindrome.com
*/


#include "Components.hpp"
#include "LevelSerializer.hpp"

#include <pugixml.hpp>

#include <cocos/platform/CCFileUtils.h>

#include <brigand/algorithms/for_each.hpp>

#include <unordered_map>


void LevelSerializer::saveLevel(entityx::EntityManager& entityManager, const b2Vec2& mapDimensions, const std::string& filename)
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto levelNode = doc.append_child("Level");

	levelNode.append_attribute("width") = mapDimensions.x;
	levelNode.append_attribute("height") = mapDimensions.y;

	std::unordered_map<entityx::Entity, pugi::xml_node> entityNodes;
	
	brigand::for_each<Components>([&entityManager, &levelNode, &entityNodes](auto componentElement)
	{
		entityManager.each<decltype(componentElement)::type>([&levelNode, &entityNodes](auto entity, const auto& component)
		{
			if (!entityNodes.count(entity))
			{
				entityNodes.emplace(entity, levelNode.append_child("Entity"));
			}

			component.save(entityNodes.at(entity).append_child());
		});
	});

	doc.save_file((cocos2d::FileUtils::getInstance()->getWritablePath() + filename).c_str());
}