/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "CombatSystem.hpp"
#include "NodeComponent.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
#include "ConversionUtility.hpp"
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

	if (shooterWeapon && shooterWeapon->isReloaded())
	{
		auto shooterBody = event.shooter.component<BodyComponent>();

		auto projectileEntity = entityParser.createEntity(shooterWeapon->getProjectileName());
		auto projectileNode = projectileEntity.component<NodeComponent>();
		auto projectileBody = projectileEntity.component<BodyComponent>();
		auto projectileSpeed = projectileEntity.component<SpeedComponent>();

		if (shooterBody && projectileNode && projectileBody && projectileSpeed)
		{
			shooterWeapon->setReloadStatus(false);

			const auto& shooterBodySize = shooterBody->getAABB().upperBound - shooterBody->getAABB().lowerBound;

			auto projectileDirection = event.targetPosition - shooterBody->getPosition();
			projectileDirection.Normalize();

			b2Vec2 projectilePosition(projectileDirection.x * shooterBodySize.x, projectileDirection.y * shooterBodySize.y);
			projectilePosition += shooterBody->getPosition();

			projectileNode->setPosition(Utility::worldToScreenCoordinates(projectilePosition));
			projectileNode->setRotation(Utility::radiansToDegrees(shooterBody->getAngle()));
			projectileBody->setPosition(projectilePosition);
			projectileBody->setAngle(shooterBody->getAngle());
			projectileBody->applyLinearImpulse(projectileSpeed->getMaxLinearSpeed() * projectileDirection);
		}
	}
}

void CombatSystem::receive(const EntityDied& event)
{
	auto node = event.entity.component<NodeComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto explosion = event.entity.component<ExplosionComponent>();

	if (node && body && explosion)
	{


	
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
		}
	}
}