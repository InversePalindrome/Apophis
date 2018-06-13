/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "Conversions.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"


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
	
}

void ItemSystem::receive(const PickedUpItem& event)
{	
	if (auto weapon = event.itemEntity.component<WeaponComponent>())
	{
		addWeapon(event.entity, weapon);
	}
	if (auto regenBoost = event.itemEntity.component<RegenBoostComponent>())
	{
		addRegenBoost(event.entity, regenBoost);
	}
	if (auto speedBoost = event.itemEntity.component<SpeedBoostComponent>())
	{
		addSpeedBoost(event.entity, speedBoost);
	}

	event.itemEntity.destroy();
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

		entitySpeed->setMaxLinearSpeed(entitySpeed->getMaxLinearSpeed() * speedBoost->getSpeedBoostPercent());

		timer.add(speedBoost->getSpeedBoostDuration(), [entitySpeed, originalSpeed](auto id) mutable
		{
			if (entitySpeed)
			{
				entitySpeed->setMaxLinearSpeed(originalSpeed);
			}
		});
	}
}