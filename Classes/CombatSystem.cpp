/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "NodeComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "ExplosionComponent.hpp"


CombatSystem::CombatSystem(EntityFactory& entityFactory) :
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

	auto node = entity.component<NodeComponent>();
	auto body = entity.component<BodyComponent>();
	auto explosion = entity.component<ExplosionComponent>();

	if (node && body && explosion)
	{
		const auto& bodyPosition = body->getPosition();

		const auto& explosionName = explosion->getExplosionName();
		auto explosionTime = explosion->getExplosionTime();

		node->scheduleOnce([this, bodyPosition, explosionName, explosionTime](auto dt)
		{
			auto explosionEntity = entityFactory.createEntity(explosionName);
			
			eventManager->emit(SetPosition{ explosionEntity, bodyPosition });
			eventManager->emit(PlayAction{ explosionEntity, "Explosion", false });
	
			if (auto explosionNode = explosionEntity.component<NodeComponent>())
			{
				explosionNode->scheduleOnce([explosionEntity](auto dt) mutable { explosionEntity.destroy(); }, explosionTime, "Destroy");
			}
		}, 0.f, "CreateExplosion");
	}
}

void CombatSystem::receive(const ProjectileHit& event)
{
	auto victimNode = event.victim.component<NodeComponent>();
	auto victimHealth = event.victim.component<HealthComponent>();
	auto projectileNode = event.projectile.component<NodeComponent>();
	auto projectileDamage = event.projectile.component<DamageComponent>();

	if (victimNode && victimHealth && projectileNode && projectileDamage)
	{
		victimHealth->setCurrentHitpoints(victimHealth->getCurrentHitpoints() - projectileDamage->getDamageHitpoints());

		if (victimHealth->getCurrentHitpoints() <= 0.f)
		{
			eventManager->emit(EntityDied{ event.victim });

			victimNode->scheduleOnce([event](auto dt) { event.victim.destroy(); }, 0.f, "Destroy");
		}

		projectileNode->scheduleOnce([event](auto dt){ event.projectile.destroy(); }, 0.f, "Destroy");
	}
}