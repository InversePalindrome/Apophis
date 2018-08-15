/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntitySerializer.cpp
InversePalindrome.com
*/


#include "Components.hpp"
#include "EntitySerializer.hpp"

#include <brigand/algorithms/for_each.hpp>


void EntitySerializer::saveEntity(entityx::Entity entity, const std::string& filename)
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	saveEntity(entity, doc.append_child("Entity"));
	
	doc.save_file(filename.c_str());
}

void EntitySerializer::saveEntity(entityx::Entity entity, pugi::xml_node& entityNode)
{
	brigand::for_each<Components>([&entity, &entityNode](auto componentType) 
	{
		if (const auto component = entity.component<decltype(componentType)::type>())
		{
			component->save(entityNode.append_child());
		}
	});
}