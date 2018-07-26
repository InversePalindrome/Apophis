/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityFactory.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <pugixml.hpp>

#include <string>
#include <functional>
#include <unordered_map>


class EntityFactory
{
public:
	EntityFactory(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);
	EntityFactory(const EntityFactory&) = delete;
	EntityFactory& operator=(const EntityFactory&) = delete;

	entityx::Entity createEntity(const std::string& name);
	entityx::Entity createEntity(const pugi::xml_node& entityNode);

	void createEntities(const std::string& filename);

private:
	entityx::EntityManager& entityManager;
	entityx::EventManager& eventManager;

	const std::unordered_map<std::string, std::function<void(entityx::Entity&, const pugi::xml_node&)>> componentParsers;
	
	void parseEntity(entityx::Entity& entity, const pugi::xml_node& entityNode);
};