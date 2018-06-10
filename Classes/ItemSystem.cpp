/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "DropComponent.hpp"
#include "NodeComponent.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "ConversionUtility.hpp"


ItemSystem::ItemSystem(EntityParser& entityParser) :
	entityParser(entityParser)
{
}

void ItemSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityDied>(*this);
	eventManager.subscribe<PickedUpItem>(*this);
}

void ItemSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{

}

void ItemSystem::receive(const EntityDied& event)
{
	auto drop = event.entity.component<DropComponent>();
	auto body = event.entity.component<BodyComponent>();

	if (drop && body)
	{
		auto dropEntity = entityParser.createEntity(drop->getItem());

		if (auto dropNode = dropEntity.component<NodeComponent>())
		{
		    dropNode->setPosition(Utility::worldToScreenCoordinates(body->getPosition()));
		}
		if (auto dropBody = dropEntity.component<BodyComponent>())
		{
			dropBody->setPosition(body->getPosition());
		}
	}
}

void ItemSystem::receive(const PickedUpItem& event)
{	
	if (auto weapon = event.itemEntity.component<WeaponComponent>())
	{
		addWeapon(event.entity, weapon);
	}
	if (auto regenBoost = event.itemEntity.component<RegenBoostComponent>())
	{

	}
	if (auto speedBoost = event.itemEntity.component<SpeedBoostComponent>())
	{

	}
}

void ItemSystem::addWeapon(entityx::Entity entity, entityx::ComponentHandle<WeaponComponent> weapon)
{
	entity.replace<WeaponComponent>(*weapon.get());
}

void ItemSystem::addRegenBoost(entityx::Entity entity, entityx::ComponentHandle<RegenBoostComponent> regenBoost)
{
	if (auto entityHealth = entity.component<HealthComponent>())
	{ 
		auto hitpointBoost = regenBoost->getHitpointBoost();
		
		timer.add(regenBoost->getRegenRate(), [entityHealth, hitpointBoost](auto id) mutable
		{
			if (entityHealth)
			{
				auto regenHealth = entityHealth->getCurrentHitpoints() + hitpointBoost;

				if (regenHealth <= entityHealth->getMaxHitpoints())
				{
					entityHealth->setCurrentHitpoints(regenHealth);
				}
			}
		}, regenBoost->getRegenPeriod());
	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::ComponentHandle<SpeedBoostComponent> speedBoost)
{
	if (auto entitySpeed = entity.component<SpeedComponent>())
	{
		auto originalSpeed = entitySpeed->getMaxLinearSpeed();

		entitySpeed->setMaxLinearSpeed(entitySpeed->getMaxLinearSpeed() * speedBoost->getSpeedBoost());

		timer.add(speedBoost->getSpeedBoostDuration(), [entitySpeed, originalSpeed](auto id) mutable
		{
			if (entitySpeed)
			{
				entitySpeed->setMaxLinearSpeed(originalSpeed);
			}
		});
	}
}