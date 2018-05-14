/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AISystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "AISystem.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"


void AISystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityCreated>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<BehaviorTreeComponent>>(*this);
}

void AISystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	if (playerBody.valid())
	{
		entityx::ComponentHandle<AI> ai;
		entityx::ComponentHandle<BehaviorTreeComponent> tree;

		for (auto entity : entityManager.entities_with_components(ai, tree))
		{
			tree->update(entity);
		}
	}
}

void AISystem::receive(const EntityCreated& event)
{
	if (event.entity.has_component<Player>())
	{
		if (auto playerBody = event.entity.component<BodyComponent>())
		{
			this->playerBody = playerBody;
		}
	}
}

void AISystem::receive(const entityx::ComponentAddedEvent<BehaviorTreeComponent>& event)
{
	auto tree = event.component;
	/*
	tree->setTree(beehive::Builder<entityx::Entity>()
	.selector()
		.leaf([](auto& entity)
	{
		return beehive::Status::FAILURE;
	})*/
}