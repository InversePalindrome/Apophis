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
	const auto shooterGeometry = event.shooter.component<GeometryComponent>();
	auto shooterWeapon = event.shooter.component<WeaponComponent>();

	if (shooterGeometry && shooterWeapon && shooterWeapon->isReloaded())
	{
		shooterWeapon->setReloadStatus(false);

		auto projectileEntity = entityParser.createEntity(shooterWeapon->getProjectileName());
		auto projectileGeometry = projectileEntity.component<GeometryComponent>();
		const auto projectileSpeed = projectileEntity.component<SpeedComponent>();
		auto projectileImpulse = projectileEntity.component<ImpulseComponent>();

		if (projectileGeometry && projectileSpeed && projectileImpulse)
		{
			const auto projectileDirection = wykobi::vector2d(std::cos(Conversions::degreesToRadians(shooterGeometry->getAngle())), std::sin(Conversions::degreesToRadians(shooterGeometry->getAngle())));
			const auto projectilePosition = wykobi::vector2d(projectileDirection.x * (shooterGeometry->getSize().x + projectileGeometry->getSize().x / 2.f), projectileDirection.y * (shooterGeometry->getSize().y + projectileGeometry->getSize().y / 2.f));

		    projectileGeometry->setPosition(shooterGeometry->getPosition() + projectilePosition);
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