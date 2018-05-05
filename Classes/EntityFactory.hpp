/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - EntityFactory.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/entityx.h>

#include <tinyxml2/tinyxml2.h>

#include <functional>
#include <unordered_map>


class EntityFactory
{
public:
	EntityFactory(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);
	EntityFactory(const EntityFactory&) = delete;
	EntityFactory& operator= (const EntityFactory&) = delete;

	entityx::Entity createEntity(const std::string& entityName);

private:
	entityx::EntityManager& entityManager;
	entityx::EventManager& eventManager;

	std::unordered_map<std::string, std::function<void(entityx::Entity, const tinyxml2::XMLElement* componentNode)>> parsers;
};