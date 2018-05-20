/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "ExplosionComponent.hpp"

#include <cocos/math/Vec2.h>


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

	auto body = entity.component<BodyComponent>();
	auto explosion = entity.component<ExplosionComponent>();

	if (body && explosion)
	{
		const auto& bodyPosition = body->getPosition();

		const auto& explosionName = explosion->getExplosionName();
		auto explosionTime = explosion->getExplosionTime();

		eventManager->emit(ScheduleOnce{ entity, [this, bodyPosition, explosionName, explosionTime](auto dt)
		{
			auto explosionEntity = entityFactory.createEntity(explosionName);

			eventManager->emit(SetNodePosition{ explosionEntity, cocos2d::Vec2(bodyPosition.x * PTM_RATIO, bodyPosition.y * PTM_RATIO) });
			eventManager->emit(SetBodyPosition{ explosionEntity, bodyPosition });
			eventManager->emit(PlayAction{ explosionEntity, "Explosion", false });

			eventManager->emit(ScheduleOnce{ explosionEntity, [explosionEntity](auto dt) mutable { explosionEntity.destroy(); }, explosionTime, "Destroy" });
		}, 0.f, "CreateExplosion" });
	}
}

void CombatSystem::receive(const ProjectileHit& event)
{
	auto victimHealth = event.victim.component<HealthComponent>();
	auto projectileDamage = event.projectile.component<DamageComponent>();

	if (victimHealth && projectileDamage)
	{
		victimHealth->setCurrentHitpoints(victimHealth->getCurrentHitpoints() - projectileDamage->getDamageHitpoints());

		if (victimHealth->getCurrentHitpoints() <= 0.f)
		{
			eventManager->emit(EntityDied{ event.victim });
			eventManager->emit(ScheduleOnce{ event.victim, [event](auto dt) { event.victim.destroy(); }, 0.f, "Destroy"});
		}

		eventManager->emit(ScheduleOnce{ event.projectile, [event](auto dt){ event.projectile.destroy(); }, 0.f, "Destroy" });
	}
}