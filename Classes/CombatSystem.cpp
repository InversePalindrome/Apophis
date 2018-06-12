/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "Conversions.hpp"
#include "CombatSystem.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
#include "SpatialComponent.hpp"
#include "ImpulseComponent.hpp"
#include "ExplosionComponent.hpp"


CombatSystem::CombatSystem(EntityParser& entityParser) :
	entityParser(entityParser)
{
}

void CombatSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<ShootProjectile>(*this);
	eventManager.subscribe<EntityDied>(*this);
	eventManager.subscribe<ProjectileHit>(*this);
}

void CombatSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void CombatSystem::receive(const ShootProjectile& event)
{
	auto shooterWeapon = event.shooter.component<WeaponComponent>();
	auto shooterSpatial = event.shooter.component<SpatialComponent>();

	if (shooterWeapon && shooterSpatial && shooterWeapon->isReloaded())
	{
		shooterWeapon->setReloadStatus(false);

		auto projectileEntity = entityParser.createEntity(shooterWeapon->getProjectileName());
		auto projectileSpatial = projectileEntity.component<SpatialComponent>();
		auto projectileSpeed = projectileEntity.component<SpeedComponent>();
		auto projectileImpulse = projectileEntity.component<ImpulseComponent>();

		if (projectileSpatial && projectileSpeed && projectileImpulse)
		{
			auto projectileDirection = blaze::normalize(event.targetPosition - shooterSpatial->getPosition());
		    
		    projectileSpatial->setPosition(projectileDirection * shooterSpatial->getSize() + shooterSpatial->getPosition());
			projectileSpatial->setAngle(shooterSpatial->getAngle());

			projectileImpulse += {projectileDirection[0] * projectileSpeed->getMaxLinearSpeed(), projectileDirection[1] * projectileSpeed->getMaxLinearSpeed()};

			timer.add(shooterWeapon->getReloadTime(), [shooterWeapon](auto id) mutable
			{
				if (shooterWeapon)
				{
					shooterWeapon->setReloadStatus(true);
				}
			});
		}
	}
}

void CombatSystem::receive(const EntityDied& event)
{
	auto spatial = event.entity.component<SpatialComponent>();
	auto explosion = event.entity.component<ExplosionComponent>();

	if (spatial && explosion)
	{
		auto explosionEntity = entityParser.createEntity(explosion->getExplosionName());

		if (auto explosionSpatial = explosionEntity.component<SpatialComponent>())
		{
			explosionSpatial->setPosition(spatial->getPosition());

			timer.add(explosion->getExplosionTime(), [explosionEntity](auto id) mutable
			{
				if (explosionEntity)
				{
					explosionEntity.destroy();
				}
			});
		}
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

			event.victim.destroy();
		}
		
		event.projectile.destroy();
	}
}