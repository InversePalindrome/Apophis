/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AISystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "AISystem.hpp"
#include "AIComponent.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"


AISystem::AISystem()
{
	initStrikerTree();
}

void AISystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityCreated>(*this);
}

void AISystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<AIComponent> ai;

	for (auto entity : entityManager.entities_with_components(ai))
	{
		switch (ai->getBehaviorType())
		{
		case BehaviorType::Striker:
			strikerTree.process(entity);
			break;
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

void AISystem::initStrikerTree()
{
	strikerTree = beehive::Builder<entityx::Entity>()
	.selector()
	.sequence()
	.leaf([this](auto& entity)
	{
		auto body = entity.component<BodyComponent>();
		auto vision = entity.component<VisionComponent>();

		if (body && vision && playerBody.valid())
		{
			auto distanceFromPlayer = (playerBody->getPosition() - body->getPosition()).Length();

			if (distanceFromPlayer <= vision->getVisionDistance())
			{
				return beehive::Status::SUCCESS;
			}
		}

		return beehive::Status::FAILURE;
	})
	.selector()
	.leaf([this](auto& entity)
	{
		auto health = entity.component<HealthComponent>();

		if (health && playerBody.valid())
		{
			if (health->getCurrentHitpoints() >= health->getMaxHitpoints() * 0.2)
			{
				eventManager->emit(Seek{ entity });
				eventManager->emit(ShootProjectile{ entity, playerBody->getPosition() });

				return beehive::Status::SUCCESS;
			}
		}

		return beehive::Status::FAILURE;
	})
	.void_leaf([this](auto& entity)
	{
		eventManager->emit(Flee{ entity });
	}).end().end()
	.void_leaf([this](auto& entity)
	{
		eventManager->emit(Wander{ entity });
	})
	.end().build();
}