/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CombatSystem.cpp
InversePalindrome.com
*/


#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "WeaponComponent.hpp"
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
	eventManager.subscribe<ShootProjectile>(*this);
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
	
			gameNode->scheduleOnce([explosionEntity](auto dt) mutable
			{
				explosionEntity.destroy();
			}, explosionTime, "DestroyExplosion");
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

void CombatSystem::receive(const ShootProjectile& event)
{
	auto shooter = event.entity;
	auto weapon = shooter.component<WeaponComponent>();

	if (weapon && weapon->isReloaded())
	{
		auto projectile = entityFactory.createEntity(weapon->getProjectileName());

		auto entityBody = shooter.component<BodyComponent>();
		auto projectileBody = projectile.component<BodyComponent>();
		auto projectileSpeed = projectile.component<SpeedComponent>();
		
		if (entityBody && projectileBody && projectileSpeed)
		{
		   	const auto& entityBodySize = entityBody->getAABB().upperBound - entityBody->getAABB().lowerBound;

			auto direction = event.targetPosition - entityBody->getPosition();
			direction.Normalize();

			eventManager->emit(SetPosition{ projectile, entityBody->getPosition() + b2Vec2(direction.x * entityBodySize.x, direction.y * entityBodySize.y) });
			eventManager->emit(SetRotation{ projectile, entityBody->getAngle() });
			eventManager->emit(ApplyLinearImpulse{ projectile, projectileSpeed->getMaxSpeed() * direction - projectileBody->getLinearVelocity() });
			eventManager->emit(PlayAction{ shooter, "Shoot", false });
		}
		
		weapon->setReloadStatus(false);
		
		gameNode->scheduleOnce([shooter, weapon](auto dt) mutable
		{
			if (shooter.valid())
			{
				weapon->setReloadStatus(true);
			}
		}, weapon->getReloadTime(), "reload");
	}
}