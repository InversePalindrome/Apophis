/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntitySerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <pugixml.hpp>

#include <string>


namespace EntitySerializer
{
    void saveEntity(entityx::Entity entity, const std::string& filename);
    void saveEntity(entityx::Entity entity, pugi::xml_node& entityNode);
}