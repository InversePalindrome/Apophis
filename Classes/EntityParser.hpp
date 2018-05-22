/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <tinyxml2/tinyxml2.h>

#include <string>
#include <functional>
#include <unordered_map>


class EntityParser
{
public:
	EntityParser(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);
	EntityParser(const EntityParser&) = delete;
	EntityParser& operator= (const EntityParser&) = delete;

	entityx::Entity createEntity(const std::string& filename);

	void createEntities(const std::string& filename);

private:
	entityx::EntityManager& entityManager;
	entityx::EventManager& eventManager;
	
	std::unordered_map<std::string, std::function<void(entityx::Entity)>> tagParsers;
	std::unordered_map<std::string, std::function<void(entityx::Entity, const tinyxml2::XMLElement*)>> componentParsers;
};