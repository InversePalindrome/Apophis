/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ControlSystem.cpp
InversePalindrome.com
*/


#include "ControlSystem.hpp"
#include "BodyComponent.hpp"
#include "NodeComponent.hpp"
#include "SpeedComponent.hpp"
#include "PhysicsUtility.hpp"
#include "WeaponComponent.hpp"
#include "ImpulseComponent.hpp"


ControlSystem::ControlSystem(EntityFactory& entityFactory) :
	entityFactory(entityFactory)
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
	auto shooterNode = shooter.component<NodeComponent>();
	auto shooterBody = shooter.component<BodyComponent>();
	auto shooterWeapon = shooter.component<WeaponComponent>();

	if (shooterNode && shooterBody && shooterWeapon && shooterWeapon->isReloaded())
	{
		auto projectile = entityFactory.createEntity(shooterWeapon->getProjectileName());

		auto projectileBody = projectile.component<BodyComponent>();
		auto projectileSpeed = projectile.component<SpeedComponent>();

		if (projectileBody && projectileSpeed)
		{
			const auto& shooterBodySize = shooterBody->getAABB().upperBound - shooterBody->getAABB().lowerBound;

			auto direction = event.targetPosition - shooterBody->getPosition();
			direction.Normalize();

			eventManager->emit(SetPosition{ projectile, shooterBody->getPosition() + b2Vec2(direction.x * shooterBodySize.x, direction.y * shooterBodySize.y) });
			eventManager->emit(SetRotation{ projectile, shooterBody->getAngle() });
			eventManager->emit(MoveEntity{ projectile, direction });
			eventManager->emit(PlayAction{ shooter, "Shoot", false });

			shooterWeapon->setReloadStatus(false);

			shooterNode->scheduleOnce([shooterWeapon](auto dt) mutable
			{
				shooterWeapon->setReloadStatus(true);
			}, shooterWeapon->getReloadTime(), "Reload");
		}
	}
}