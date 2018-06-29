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

	entityx::Entity createEntity(const std::string& filename);

private:
	entityx::EntityManager& entityManager;
	entityx::EventManager& eventManager;
	
	std::unordered_map<std::string, std::function<void(entityx::Entity, const pugi::xml_node&)>> componentParsers;
	std::unordered_map<std::string, std::function<void(entityx::Entity)>> tagParsers;
};