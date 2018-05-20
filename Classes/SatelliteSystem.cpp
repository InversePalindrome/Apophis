/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "SatelliteSystem.hpp"


void SatelliteSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<Satellite> satellite;
	
	for (auto entity : entityManager.entities_with_components(satellite))
	{
		
	}
}