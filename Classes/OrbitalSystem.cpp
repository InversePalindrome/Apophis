/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "OrbitalSystem.hpp"


void OrbitalSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<Satellite> satellite;
	
	for (auto entity : entityManager.entities_with_components(satellite))
	{
		
	}
}