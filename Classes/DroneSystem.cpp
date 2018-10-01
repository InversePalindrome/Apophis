/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.cpp
InversePalindrome.com
*/


#include "DroneSystem.hpp"
#include "TagsComponent.hpp"


DroneSystem::DroneSystem(entityx::EventManager& eventManager) :
	eventManager(eventManager),
	droneTree(beehive::Builder<DroneContext>().
	leaf([](auto& context)
    {
	   return true;   
    }).end().build())
{
}

void DroneSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<EntityParsed>(*this);
}

void DroneSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityManager.each<TagsComponent>([this](auto entity, const auto& tags)
	{
		if (tags.hasTag("Drone"))
		{
			droneTree.process(DroneContext{});
		}
	});
}

void DroneSystem::receive(const EntityParsed& event)
{
	if (const auto&[tags, transform] = event.entity.components<TagsComponent, TransformComponent>(); tags && tags->hasTag("Player") && transform)
	{
		playerTransform = transform;
	}
}