/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "ItemComponent.hpp"
#include "DropComponent.hpp"
#include "NodeComponent.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "WeaponComponent.hpp"
#include "PowerUpComponent.hpp"
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
	if (auto item = event.itemEntity.component<ItemComponent>())
	{
		switch (item->getItem())
		{
		case Item::Weapon:
			addWeapon(event.entity, event.itemEntity);
			break;
		case Item::RegenBoost:
			addRegenBoost(event.entity, event.itemEntity);
			break;
		case Item::SpeedBoost:
			addSpeedBoost(event.entity, event.itemEntity);
			break;
		}
	}

	eventManager->emit(PlayAction{ event.itemEntity, "Pickup", false });
}

void ItemSystem::addWeapon(entityx::Entity entity, entityx::Entity itemEntity)
{
	if (auto weapon = itemEntity.component<WeaponComponent>())
	{
		entity.replace<WeaponComponent>(*weapon.get());
	}
}

void ItemSystem::addRegenBoost(entityx::Entity entity, entityx::Entity itemEntity)
{
	auto entityHealth = entity.component<HealthComponent>();
	auto itemPowerUp = itemEntity.component<PowerUpComponent>();

	if (entityHealth && itemPowerUp)
	{ 
		auto effectBoost = itemPowerUp->getEffectBoost();
		
		timer.add(itemPowerUp->getEffectTime(), [entityHealth, effectBoost](auto id) mutable
		{
			if (entityHealth)
			{
				auto regenHealth = entityHealth->getCurrentHitpoints() + effectBoost;

				if (regenHealth <= entityHealth->getMaxHitpoints())
				{
					entityHealth->setCurrentHitpoints(regenHealth);
				}
			}
		});
	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::Entity itemEntity)
{
	auto entitySpeed = entity.component<SpeedComponent>();
	auto itemPowerUp = itemEntity.component<PowerUpComponent>();

	if (entitySpeed && itemPowerUp)
	{
		auto originalSpeed = entitySpeed->getMaxLinearSpeed();

		entitySpeed->setMaxLinearSpeed(entitySpeed->getMaxLinearSpeed() * (1 + itemPowerUp->getEffectBoost()));

		timer.add(itemPowerUp->getEffectTime(), [entitySpeed, originalSpeed](auto id) mutable
		{
			if (entitySpeed)
			{
				entitySpeed->setMaxLinearSpeed(originalSpeed);
			}
		});
	}
}