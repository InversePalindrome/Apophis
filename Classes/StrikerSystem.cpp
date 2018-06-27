/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "StrikerSystem.hpp"
#include "SteeringBehaviors.hpp"


StrikerSystem::StrikerSystem() 
{
}
	  
void StrikerSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityCreated>(*this);
}

void StrikerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<Striker> striker;
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;
	entityx::ComponentHandle<WanderComponent> wander;
	entityx::ComponentHandle<VisionComponent> vision;
	entityx::ComponentHandle<HealthComponent> health;

	for (auto entity : entityManager.entities_with_components(striker, body, speed, wander, vision, health))
	{
		strikerTree.process(StrikerContext{ entity, body, speed, wander, vision, health });
	}
}

void StrikerSystem::receive(const EntityCreated& event)
{
	auto entity = event.entity;

	if (entity.has_component<Player>())
	{
		playerBody = entity.component<BodyComponent>();
	}
}