/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <pugixml.hpp>


namespace EntityParser
{
	void parseEntity(entityx::Entity entity, entityx::EventManager& eventManager, const std::string& filename);
	void parseEntity(entityx::Entity entity, entityx::EventManager& eventManager, const pugi::xml_node& entityNode);
}