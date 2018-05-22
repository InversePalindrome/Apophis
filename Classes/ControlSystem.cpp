/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ControlSystem.cpp
InversePalindrome.com
*/


#include "ControlSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "PhysicsUtility.hpp"
#include "WeaponComponent.hpp"
#include "ImpulseComponent.hpp"


ControlSystem::ControlSystem(EntityParser& entityParser) :
	entityParser(entityParser)
{
}

void ControlSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<MoveEntity>(*this);
	eventManager.subscribe<RotateEntity>(*this);
	eventManager.subscribe<ShootProjectile>(*this);
}

void ControlSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;

	for (auto entity : entityManager.entities_with_components(body, speed))
	{
		auto velocity = body->getLinearVelocity();

		if (velocity.Length() > speed->getMaxSpeed())
		{
			body->setLinearVelocity(speed->getMaxSpeed() / velocity.Length() * velocity);
		}
	}
}

void ControlSystem::receive(const MoveEntity& event)
{
	if (auto impulse = event.entity.component<ImpulseComponent>())
	{
		eventManager->emit(ApplyLinearImpulse{ event.entity, impulse->getImpulse() * event.direction });
	}
}

void ControlSystem::receive(const RotateEntity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		eventManager->emit(ApplyAngularImpulse{ event.entity, Utility::angularImpulseToAngle(body->getAngle(), Utility::vectorToRadian(event.direction), body->getAngularVelocity(), body->getInertia()) });
	}
}

void ControlSystem::receive(const ShootProjectile& event)
{
	auto shooter = event.entity;
	auto shooterBody = shooter.component<BodyComponent>();
	auto shooterWeapon = shooter.component<WeaponComponent>();

	if (shooterBody && shooterWeapon && shooterWeapon->isReloaded())
	{
		auto projectile = entityParser.createEntity(shooterWeapon->getProjectileName());
		auto projectileBody = projectile.component<BodyComponent>();
		auto projectileSpeed = projectile.component<SpeedComponent>();

		if (projectileBody && projectileSpeed)
		{
			auto shooterBodySize = shooterBody->getAABB().upperBound - shooterBody->getAABB().lowerBound;

			auto projectileDirection = event.targetPosition - shooterBody->getPosition();
			projectileDirection.Normalize();

			b2Vec2 projectilePosition(projectileDirection.x * shooterBodySize.x, projectileDirection.y * shooterBodySize.y);
			projectilePosition += shooterBody->getPosition();

			eventManager->emit(SetNodePosition{ projectile, {projectilePosition.x * PTM_RATIO, projectilePosition.y * PTM_RATIO} });
			eventManager->emit(SetBodyPosition{ projectile, projectilePosition });
			eventManager->emit(SetBodyAngle{ projectile, shooterBody->getAngle() });
			eventManager->emit(MoveEntity{ projectile, projectileDirection });
			eventManager->emit(PlayAction{ shooter, "Shoot", false });

			shooterWeapon->setReloadStatus(false);

			eventManager->emit(ScheduleOnce{shooter, [shooterWeapon](auto dt) mutable
			{
				shooterWeapon->setReloadStatus(true);
			}, shooterWeapon->getReloadTime(), "Reload"	});
		}
	}
}