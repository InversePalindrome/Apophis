/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ItemSystem.cpp
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
	auto node = entity.component<NodeComponent>();

	if (drop && body && node)
	{
		auto randomChance = cocos2d::rand_0_1();

		for (const auto& [range, name] : drop->getDropChances())
		{
			if (randomChance <= range)
			{
				const auto& bodyPosition = body->getPosition();

				node->scheduleOnce([this, name, bodyPosition](auto dt)
				{
					auto dropEntity = entityFactory.createEntity(name);

					eventManager->emit(SetPosition{ dropEntity, bodyPosition });
				}, 0.f, "CreateDrop");

				break;
			}
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

	if (auto itemNode = event.itemEntity.component<NodeComponent>())
	{
		itemNode->scheduleOnce([event](auto dt) { event.itemEntity.destroy(); }, 0.f, "Destroy");
	}
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
	auto entityNode = entity.component<NodeComponent>();
	auto entityHealth = entity.component<HealthComponent>();
	auto itemPowerUp = itemEntity.component<PowerUpComponent>();

	if (entityNode && entityHealth && itemPowerUp)
	{
		auto effectBoost = itemPowerUp->getEffectBoost();

		entityNode->schedule([entityHealth, effectBoost](auto dt) mutable
		{
			auto regenHealth = entityHealth->getCurrentHitpoints() + effectBoost;

			if (regenHealth <= entityHealth->getMaxHitpoints())
			{
				entityHealth->setCurrentHitpoints(regenHealth);
			}
		}, 1.f, static_cast<int>(itemPowerUp->getEffectTime()), 0.f, "RegenBoost");
	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::Entity itemEntity)
{
	auto entityNode = entity.component<NodeComponent>();
	auto entitySpeed = entity.component<SpeedComponent>();
	auto itemPowerUp = itemEntity.component<PowerUpComponent>();

	if (entityNode && entitySpeed && itemPowerUp)
	{
		auto originalSpeed = entitySpeed->getMaxSpeed();

		entitySpeed->setMaxSpeed(entitySpeed->getMaxSpeed() * (1 + itemPowerUp->getEffectBoost()));

		entityNode->scheduleOnce([entitySpeed, originalSpeed](auto dt) mutable
		{
			entitySpeed->setMaxSpeed(originalSpeed);
		}, itemPowerUp->getEffectTime(), "SpeedBoost");
	}
}