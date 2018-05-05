/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
#include "ExplosionComponent.hpp"


CombatSystem::CombatSystem(cocos2d::Node* mainNode, EntityFactory& entityFactory) :
	mainNode(mainNode),
	entityFactory(entityFactory)
{
}

void CombatSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<ShootProjectile>(*this);
	eventManager.subscribe<CombatOcurred>(*this);
	eventManager.subscribe<EntityDied>(*this);
}

void CombatSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void CombatSystem::receive(const CombatOcurred& event)
{
	handleHitpoints(event.attacker, event.victim);
}

void CombatSystem::receive(const ShootProjectile& event)
{
	auto weapon = event.entity.component<WeaponComponent>();

	if (weapon && weapon->isReloaded())
	{
		auto projectile = entityFactory.createEntity(weapon->getProjectileName());

		auto entityBody = event.entity.component<BodyComponent>();
		auto projectileBody = projectile.component<BodyComponent>();
		auto projectileSpeed = projectile.component<SpeedComponent>();
		
		if (entityBody && projectileBody && projectileSpeed)
		{
			auto direction = event.targetPosition - entityBody->getPosition();
			direction.Normalize();

			const auto& entityBodySize = entityBody->getAABB().upperBound - entityBody->getAABB().lowerBound;

			eventManager->emit(SetPosition{ projectile, entityBody->getPosition() + b2Vec2(direction.x * entityBodySize.x, direction.y * entityBodySize.y) });
			eventManager->emit(SetRotation{ projectile, entityBody->getAngle() });
			eventManager->emit(ApplyLinearImpulse{ projectile, projectileSpeed->getMaxSpeed() * direction - projectileBody->getLinearVelocity() });
			eventManager->emit(PlayAction{ event.entity, "Shoot", false });
		}
		
		weapon->setReloadStatus(false);

		mainNode->scheduleOnce([weapon](float t) mutable
		{
			weapon->setReloadStatus(true);
		}, weapon->getReloadTime(), "reload");
	}
}

void CombatSystem::receive(const EntityDied& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto explosion = event.entity.component<ExplosionComponent>();

	if (body && explosion)
	{
		const auto& bodyPosition = body->getPosition();
		const auto& explosionName = explosion->getExplosionName();
		auto explosionTime = explosion->getExplosionTime();

		auto explosionEntity = entityFactory.createEntity(explosionName);

		eventManager->emit(SetPosition{ explosionEntity, bodyPosition });
		eventManager->emit(PlayAction{ explosionEntity, "Explosion", false });
				
        mainNode->scheduleOnce([explosionEntity](float t) mutable
	   {
		  explosionEntity.destroy();
	   }, explosionTime, "destroy");
	}
}

void CombatSystem::handleHitpoints(entityx::Entity attacker, entityx::Entity victim)
{
	auto health = victim.component<HealthComponent>();
	auto damage = attacker.component<DamageComponent>();

	if (health && damage)
	{
		health->setHitpoints(health->getHitpoints() - damage->getHitpoints());
		 
		if (health->getHitpoints() <= 0)
		{
			eventManager->emit(EntityDied{ victim });

			victim.destroy();
		}
	}
}