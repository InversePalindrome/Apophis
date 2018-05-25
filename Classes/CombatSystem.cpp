/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "MathUtility.hpp"
#include "CombatSystem.hpp"
#include "NodeComponent.hpp"
#include "BodyComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "WeaponComponent.hpp"
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
	auto shooterBody = event.shooter.component<BodyComponent>();
	auto shooterWeapon = event.shooter.component<WeaponComponent>();

	if (shooterBody && shooterWeapon && shooterWeapon->isReloaded())
	{
		shooterWeapon->setReloadStatus(false);

		const auto& shooterBodySize = shooterBody->getAABB().upperBound - shooterBody->getAABB().lowerBound;

		auto projectileDirection = event.targetPosition - shooterBody->getPosition();
		projectileDirection.Normalize();

		b2Vec2 projectilePosition(projectileDirection.x * shooterBodySize.x, projectileDirection.y * shooterBodySize.y);
		projectilePosition += shooterBody->getPosition();

		auto projectileEntity = entityParser.createEntity(shooterWeapon->getProjectileName());

		eventManager->emit(SetNodePosition{ projectileEntity,{ projectilePosition.x * Constants::PTM_RATIO, projectilePosition.y * Constants::PTM_RATIO } });
		eventManager->emit(SetNodeRotation{ projectileEntity, Utility::radiansToDegrees(shooterBody->getAngle()) });
		eventManager->emit(SetBodyPosition{ projectileEntity, projectilePosition });
		eventManager->emit(SetBodyAngle{ projectileEntity, shooterBody->getAngle() });
		eventManager->emit(ApplyLinearImpulse{ projectileEntity, projectileDirection });
		eventManager->emit(PlayAction{ event.shooter, "Shoot", false });
		eventManager->emit(ScheduleOnce{ event.shooter, [shooterWeapon](auto dt) mutable { shooterWeapon->setReloadStatus(true); }, shooterWeapon->getReloadTime(), "Reload" });
	}
}

void CombatSystem::receive(const EntityDied& event)
{
	auto node = event.entity.component<NodeComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto explosion = event.entity.component<ExplosionComponent>();

	if (node && body && explosion)
	{
		const auto& nodePosition = node->getPosition();
		const auto& bodyPosition = body->getPosition();
		const auto& explosionName = explosion->getExplosionName();
		auto explosionTime = explosion->getExplosionTime();

		eventManager->emit(ScheduleOnce{ event.entity, [this, nodePosition, bodyPosition, explosionName, explosionTime](auto dt)
		{
			auto explosionEntity = entityParser.createEntity(explosionName);

			eventManager->emit(SetNodePosition{ explosionEntity, nodePosition });
			eventManager->emit(SetBodyPosition{ explosionEntity, bodyPosition });
			eventManager->emit(PlayAction{ explosionEntity, "Explosion", false });
			eventManager->emit(ScheduleOnce{ explosionEntity, [explosionEntity](auto dt) mutable { explosionEntity.destroy(); }, explosionTime, "Destroy" });
		}, 0.f, "Create" });
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