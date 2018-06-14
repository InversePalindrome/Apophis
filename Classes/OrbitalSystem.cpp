/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.cpp
InversePalindrome.com
*/


#include "OrbitalSystem.hpp"
#include "SpeedComponent.hpp"
#include "ImpulseComponent.hpp"
#include "GeometryComponent.hpp"
#include "SteeringBehaviors.hpp"
#include "SatelliteComponent.hpp"


void OrbitalSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<SatelliteComponent> satellite;
	entityx::ComponentHandle<GeometryComponent> geometry;
	entityx::ComponentHandle<ImpulseComponent> impulse;
	entityx::ComponentHandle<SpeedComponent> speed;
	
	for (auto entity : entityManager.entities_with_components(satellite, geometry, speed, impulse))
	{
		if (auto primaryEntity = entityManager.get(entityManager.create_id(satellite->getPrimaryID())))
		{
			if (auto primaryGeometry = primaryEntity.component<GeometryComponent>())
			{
				//impulse += SteeringBehaviors::orbit(primaryGeometry->getPosition(), primaryBody->getPosition(), speed->getMaxLinearSpeed());
			}
		}
	}
}