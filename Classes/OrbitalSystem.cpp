/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "OrbitalSystem.hpp"
#include "BodyComponent.hpp"
#include "SatelliteComponent.hpp"


OrbitalSystem::OrbitalSystem(entityx::EntityManager& entityManager) :
	entityManager(entityManager)
{
}

void OrbitalSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SatelliteComponent> satellite;
	
	for (auto entity : entityManager.entities_with_components(body, satellite))
	{
		if (auto primaryEntity = entityManager.get(entityManager.create_id(satellite->getPrimaryID())))
		{
			if (auto primaryBody = primaryEntity.component<BodyComponent>())
			{
				eventManager.emit(Orbit{ entity, primaryBody->getPosition() });
			}
		}
	}
}