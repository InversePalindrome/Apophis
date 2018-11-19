/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSerializer.cpp
InversePalindrome.com
*/


#include "LevelSerializer.hpp"
#include "EntitySerializer.hpp"

#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


void LevelSerializer::saveLevel(const std::vector<entityx::Entity>& entities, const b2Vec2& mapDimensions, const std::string& filename)
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto levelNode = doc.append_child("Level");

	levelNode.append_attribute("width") = mapDimensions.x;
	levelNode.append_attribute("height") = mapDimensions.y;

	for (const auto& entity : entities)
	{
		EntitySerializer::saveEntity(entity, levelNode.append_child("Entity"));
	}

	doc.save_file(filename.c_str());
}