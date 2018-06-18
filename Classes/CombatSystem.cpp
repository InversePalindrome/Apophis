/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "CombatSystem.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
#include "ImpulseComponent.hpp"
#include "GeometryComponent.hpp"
#include "ExplosionComponent.hpp"


CombatSystem::CombatSystem(EntityParser& entityParser) :
	entityParser(entityParser)
{
}

void CombatSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<ShootProjectile>(*this);
	eventManager.subscribe<ProjectileHit>(*this);
}

void CombatSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void CombatSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto deadEntity = event.entity;
	
	auto deadGeometry = deadEntity.component<GeometryComponent>();
	const auto deadExplosion = deadEntity.component<ExplosionComponent>();
	
	if (deadGeometry && deadExplosion)
	{
		auto explosionEntity = entityParser.createEntity(deadExplosion->getExplosionName());
		
		if (auto explosionGeometry = explosionEntity.component<GeometryComponent>())
		{
			explosionGeometry->setPosition(deadGeometry->getPosition());
			
			timer.add(deadExplosion->getExplosionTime(), [explosionEntity](auto id) mutable
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

void CombatSystem::receive(const ShootProjectile& event)
{
	auto shooterWeapon = event.shooter.component<WeaponComponent>();
	const auto shooterGeometry = event.shooter.component<GeometryComponent>();

	if (shooterWeapon && shooterGeometry && shooterWeapon->isReloaded())
	{
		shooterWeapon->setReloadStatus(false);

		auto projectileEntity = entityParser.createEntity(shooterWeapon->getProjectileName());
		auto projectileGeometry = projectileEntity.component<GeometryComponent>();
		const auto projectileSpeed = projectileEntity.component<SpeedComponent>();
		auto projectileImpulse = projectileEntity.component<ImpulseComponent>();

		if (projectileGeometry && projectileSpeed && projectileImpulse)
		{
			const auto shooterSize = shooterGeometry->getAABB()[1] - shooterGeometry->getAABB()[0];
			const auto projectileDirection = wykobi::normalize(event.targetPosition - shooterGeometry->getPosition());
			const auto projectilePosition = shooterGeometry->getPosition() + wykobi::vector2d(projectileDirection.x * shooterSize.x, projectileDirection.y * shooterSize.y);
	
		    projectileGeometry->setPosition(projectilePosition);
			projectileGeometry->setAngle(shooterGeometry->getAngle());

			projectileImpulse += {projectileDirection.x * projectileSpeed->getMaxLinearSpeed(), projectileDirection.y * projectileSpeed->getMaxLinearSpeed()};

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

void CombatSystem::receive(const ProjectileHit& event)
{
	auto victimHealth = event.victim.component<HealthComponent>();
	const auto projectileDamage = event.projectile.component<DamageComponent>();

	if (victimHealth && projectileDamage)
	{
		victimHealth->setCurrentHitpoints(victimHealth->getCurrentHitpoints() - projectileDamage->getDamageHitpoints());

		if (victimHealth->getCurrentHitpoints() <= 0.f)
		{
			event.victim.destroy();
		}
		
		event.projectile.destroy();
	}
}