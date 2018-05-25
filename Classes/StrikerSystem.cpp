/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "StrikerSystem.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"


StrikerSystem::StrikerSystem()
{
	initStrikerTree();
}

void StrikerSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityParsed>(*this);
}

void StrikerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<Striker> striker;

	for (auto entity : entityManager.entities_with_components(striker))
	{
		
	}
}

void StrikerSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		playerBody = event.entity.component<BodyComponent>();
	}
}

void StrikerSystem::initStrikerTree()
{
	strikerTree = beehive::Builder<entityx::Entity>()
	.selector()
	.sequence()
	.leaf([this](auto& entity)
	{
		auto body = entity.component<BodyComponent>();
		auto vision = entity.component<VisionComponent>();

		if (playerBody.valid() && body && vision && (playerBody->getPosition() - body->getPosition()).Length() <= vision->getVisionDistance())
		{
			return beehive::Status::SUCCESS;
		}

		return beehive::Status::FAILURE;
	})
	.selector()
	.leaf([this](auto& entity)
	{
		auto health = entity.component<HealthComponent>();

		if (playerBody.valid() && health)
		{
			if (health->getCurrentHitpoints() >= health->getMaxHitpoints() * 0.2)
			{
			//	eventManager->emit(Seek{ entity });
				eventManager->emit(ShootProjectile{ entity, playerBody->getPosition() });

				return beehive::Status::SUCCESS;
			}
		}

		return beehive::Status::FAILURE;
	})
	.void_leaf([this](auto& entity)
	{
		//eventManager->emit(Flee{ entity });
	}).end().end()
	.void_leaf([this](auto& entity)
	{
		//eventManager->emit(Wander{ entity });
	})
	.end().build();
}