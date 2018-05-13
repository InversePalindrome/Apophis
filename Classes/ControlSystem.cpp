/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ControlSystem.cpp
InversePalindrome.com
*/


#include "ControlSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "PhysicsUtility.hpp"
#include "WeaponComponent.hpp"
#include "ImpulseComponent.hpp"


ControlSystem::ControlSystem(cocos2d::Node* gameNode, EntityFactory& entityFactory) :
	gameNode(gameNode),
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
			eventManager->emit(MoveEntity{ projectile, direction });
			eventManager->emit(PlayAction{ shooter, "Shoot", false });
		}

		weapon->setReloadStatus(false);

		gameNode->scheduleOnce([shooter, weapon](auto dt) mutable
		{
			if (shooter.valid())
			{
				weapon->setReloadStatus(true);
			}
		}, weapon->getReloadTime(), "Reload");
	}
}