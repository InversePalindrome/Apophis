/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "ItemComponent.hpp"
#include "DropComponent.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "WeaponComponent.hpp"
#include "PowerUpComponent.hpp"


ItemSystem::ItemSystem(EntityFactory& entityFactory) :
	entityFactory(entityFactory)
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
	auto entity = event.entity;

	auto drop = entity.component<DropComponent>();
	auto body = entity.component<BodyComponent>();

	if (drop && body)
	{
		const auto& item = drop->getItem();
		const auto& bodyPosition = body->getPosition();

		eventManager->emit(ScheduleOnce{ entity, [this, item, bodyPosition](auto dt)
		{
			auto dropEntity = entityFactory.createEntity(item);

			eventManager->emit(SetPosition{ dropEntity, bodyPosition });
		}, 0.f, "CreateDrop" });
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
	eventManager->emit(ScheduleOnce{ event.itemEntity, [event](auto dt) { event.itemEntity.destroy(); }, 0.f, "Destroy"});
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

		eventManager->emit(Schedule{ entity, [entityHealth, effectBoost](auto dt) mutable
		{
			auto regenHealth = entityHealth->getCurrentHitpoints() + effectBoost;

			if (regenHealth <= entityHealth->getMaxHitpoints())
			{
				entityHealth->setCurrentHitpoints(regenHealth);
			}
		}, 1.f, static_cast<unsigned int>(itemPowerUp->getEffectTime()), 0.f, "RegenBoost" });
	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::Entity itemEntity)
{
	auto entitySpeed = entity.component<SpeedComponent>();
	auto itemPowerUp = itemEntity.component<PowerUpComponent>();

	if (entitySpeed && itemPowerUp)
	{
		auto originalSpeed = entitySpeed->getMaxSpeed();

		entitySpeed->setMaxSpeed(entitySpeed->getMaxSpeed() * (1 + itemPowerUp->getEffectBoost()));

		eventManager->emit(ScheduleOnce{ entity, [entitySpeed, originalSpeed](auto dt) mutable
		{
			entitySpeed->setMaxSpeed(originalSpeed);
		}, itemPowerUp->getEffectTime(), "SpeedBoost" });
	}
}