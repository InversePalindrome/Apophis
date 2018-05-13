/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "ExplosionComponent.hpp"


CombatSystem::CombatSystem(cocos2d::Node* gameNode, EntityFactory& entityFactory) :
	gameNode(gameNode),
	entityFactory(entityFactory)
{
}

void CombatSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityDied>(*this);
	eventManager.subscribe<ProjectileHit>(*this);
}

void CombatSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void CombatSystem::receive(const EntityDied& event)
{
	auto entity = event.entity;

	auto body = entity.component<BodyComponent>();
	auto explosion = entity.component<ExplosionComponent>();

	if (body && explosion)
	{
		const auto& bodyPosition = body->getPosition();

		const auto& explosionName = explosion->getExplosionName();
		auto explosionTime = explosion->getExplosionTime();

		gameNode->scheduleOnce([this, bodyPosition, explosionName, explosionTime](auto dt)
		{
			auto explosionEntity = entityFactory.createEntity(explosionName);
			
			eventManager->emit(SetPosition{ explosionEntity, bodyPosition });
			eventManager->emit(PlayAction{ explosionEntity, "Explosion", false });
	
			gameNode->scheduleOnce([explosionEntity](auto dt) mutable { explosionEntity.destroy(); }, explosionTime, "DestroyExplosion");
		}, 0.f, "CreateExplosion");
	}
}

void CombatSystem::receive(const ProjectileHit& event)
{
	auto health = event.victim.component<HealthComponent>();
	auto damage = event.projectile.component<DamageComponent>();

	if (health && damage)
	{
		health->setCurrentHitpoints(health->getCurrentHitpoints() - damage->getDamageHitpoints());

		if (health->getCurrentHitpoints() <= 0.f)
		{
			eventManager->emit(EntityDied{ event.victim });

			gameNode->scheduleOnce([event](auto dt) { event.victim.destroy(); }, 0.f, "DestroyVictim");
		}
	}

	gameNode->scheduleOnce([event](auto dt){ event.projectile.destroy(); }, 0.f, "DestroyProjectile");
}