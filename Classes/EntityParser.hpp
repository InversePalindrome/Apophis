/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <pugixml.hpp>

#include <functional>
#include <unordered_map>


namespace EntityParser
{
	extern const std::unordered_map<std::string, std::function<void(entityx::Entity&, entityx::EventManager&, const pugi::xml_node&)>> componentParsers;

	void parseEntity(entityx::Entity& entity, entityx::EventManager& eventManager, const std::string& filename);
	void parseEntity(entityx::Entity& entity, entityx::EventManager& eventManager, const pugi::xml_node& entityNode);
}