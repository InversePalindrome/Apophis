/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "Conversions.hpp"
#include "CombatSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
#include "ExplosionComponent.hpp"
#include "TransformComponent.hpp"


CombatSystem::CombatSystem(EntityFactory& entityFactory) :
	entityFactory(entityFactory)
{
}

void CombatSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<ShootProjectile>(*this);
	eventManager.subscribe<CombatOcurred>(*this);
}

void CombatSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void CombatSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	handleExplosion(event.entity);
}

void CombatSystem::receive(const ShootProjectile& event)
{
	if (auto [shooterWeapon, shooterBody] = event.shooter.components<WeaponComponent, BodyComponent>(); shooterWeapon && shooterBody && shooterWeapon->isReloaded())
	{
		shooterWeapon->setReloadStatus(false);
		
		auto projectileEntity = entityFactory.createEntity(shooterWeapon->getProjectileName());

		if (auto[projectileBody, projectileSpeed] = projectileEntity.components<BodyComponent, SpeedComponent>(); projectileBody && projectileSpeed)
		{
			const b2Vec2 shooterSize(shooterBody->getAABB().upperBound - shooterBody->getAABB().lowerBound);
			const b2Vec2 projectileSize(projectileBody->getAABB().upperBound - projectileBody->getAABB().lowerBound);			
			const b2Vec2 projectileDirection(std::cos(shooterBody->getAngle()), std::sin(shooterBody->getAngle()));
			const b2Vec2 velocityOffset(b2Abs(Constants::TIMESTEP * shooterBody->getLinearVelocity()));
			const b2Vec2 sizeOffset(0.5f * shooterSize + projectileSize);
			const b2Vec2 projectilePosition(projectileDirection.x * (sizeOffset.x + velocityOffset.x),  projectileDirection.y * (sizeOffset.y + velocityOffset.y));
		
			projectileBody->setPosition(shooterBody->getPosition() + projectilePosition);
			projectileBody->setAngle(shooterBody->getAngle());
			projectileBody->setLinearVelocity(shooterBody->getLinearVelocity());
			projectileBody->applyLinearImpulse(projectileSpeed->getMaxLinearSpeed() * projectileDirection);
			
			timer.add(shooterWeapon->getReloadTime(), [shooterWeapon](auto id) mutable
			{
				if (shooterWeapon)
				{
					shooterWeapon->setReloadStatus(true);
				}
			});
		}

		eventManager->emit(PlayAudio{ event.shooter, Sound::Shoot, false });
	}
}

void CombatSystem::receive(const CombatOcurred& event)
{
	auto victimHealth = event.victim.component<HealthComponent>();
	const auto attackerDamage = event.attacker.component<DamageComponent>();

	if (victimHealth && attackerDamage)
	{
		victimHealth->setCurrentHitpoints(victimHealth->getCurrentHitpoints() - attackerDamage->getDamageHitpoints());

		if (victimHealth->getCurrentHitpoints() <= 0.f)
		{
			event.victim.destroy();
		}
	}
}

void CombatSystem::handleExplosion(entityx::Entity destroyedEntity)
{
	if (const auto [destroyedTransform, destroyedExplosion] = destroyedEntity.components<TransformComponent, ExplosionComponent>();
     	destroyedTransform && destroyedExplosion)
	{
		auto explosionEntity = entityFactory.createEntity(destroyedExplosion->getExplosionName());

		if (auto explosionTransform = explosionEntity.component<TransformComponent>())
		{
			explosionTransform->setPosition(destroyedTransform->getPosition());

			timer.add(destroyedExplosion->getExplosionTime(), [explosionEntity](auto id) mutable
			{
				if (explosionEntity)
				{
					explosionEntity.destroy();
				}
			});
		}

		eventManager->emit(PlayAudio{ explosionEntity, Sound::Explode, false });
	}
}