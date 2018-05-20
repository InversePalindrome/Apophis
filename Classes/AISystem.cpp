/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AISystem.cpp
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
	initPatrollerTree();
}

void AISystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityParsed>(*this);
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
		case BehaviorType::Patroller:
			patrollerTree.process(entity);
		}
	}
}

void AISystem::receive(const EntityParsed& event)
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

void AISystem::initPatrollerTree()
{
	patrollerTree = beehive::Builder<entityx::Entity>()
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
	.void_leaf([this](auto& entity)
	{
		eventManager->emit(Pursue{ entity });
	}).end()
	.void_leaf([this](auto& entity)
	{
		eventManager->emit(Patrol{ entity });
	}).end().build();
}