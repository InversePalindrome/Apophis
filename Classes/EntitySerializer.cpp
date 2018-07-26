/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntitySerializer.cpp
InversePalindrome.com
*/


#include "Components.hpp"
#include "EntitySerializer.hpp"

#include <pugixml.hpp>

#include <cocos/platform/CCFileUtils.h>

#include <brigand/algorithms/for_each.hpp>

#include <unordered_map>


EntitySerializer::EntitySerializer(entityx::EntityManager& entityManager) :
	entityManager(entityManager)
{
}

void EntitySerializer::saveEntities(const std::string& filename)
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto entitiesNode = doc.append_child("Entities");

	std::unordered_map<entityx::Entity, pugi::xml_node> entityNodes;
	
	brigand::for_each<Components>([this, &entitiesNode, &entityNodes](auto componentElement)
	{
		entityManager.each<decltype(componentElement)::type>([&entitiesNode, &entityNodes](auto entity, const auto& component)
		{
			if (!entityNodes.count(entity))
			{
				entityNodes.emplace(entity, entitiesNode.append_child("Entity"));
			}

			component.save(entityNodes.at(entity).append_child());
		});
	});

	doc.save_file((cocos2d::FileUtils::getInstance()->getWritablePath() + filename).c_str());
}