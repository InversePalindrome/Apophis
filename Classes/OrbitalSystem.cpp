/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.cpp
InversePalindrome.com
*/


#include "OrbitalSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "SteeringBehaviors.hpp"
#include "SatelliteComponent.hpp"


void OrbitalSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<SatelliteComponent> satellite;
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;
	
	for (auto entity : entityManager.entities_with_components(satellite, body, speed))
	{
		if (auto primaryEntity = entityManager.get(entityManager.create_id(satellite->getPrimaryID())))
		{
			if (auto primaryBody = primaryEntity.component<BodyComponent>())
			{
				body->applyLinearImpulse(SteeringBehaviors::orbit(body->getPosition(), primaryBody->getPosition(), body->getLinearVelocity(), speed->getMaxLinearSpeed()));
			}
		}
	}
}