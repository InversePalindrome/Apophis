/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntitySerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <string>


class EntitySerializer
{
public:
	explicit EntitySerializer(entityx::EntityManager& entiyManagerManager);

	void saveEntities(const std::string& filename);

private:
	entityx::EntityManager& entityManager;

	std::vector<entityx::Entity> entities;
};