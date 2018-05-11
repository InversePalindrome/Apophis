/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ItemSystem.cpp
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


ItemSystem::ItemSystem(cocos2d::Node* gameNode, EntityFactory& entityFactory) :
	gameNode(gameNode),
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
		auto randomChance = cocos2d::rand_0_1();

		for (const auto&[range, name] : drop->getDropChances())
		{
			if (randomChance <= range)
			{
				const auto& bodyPosition = body->getPosition();

				gameNode->scheduleOnce([this, name, bodyPosition](auto dt)
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

	gameNode->scheduleOnce([event](auto dt) { event.itemEntity.destroy(); }, 0.f, "DestroyItem");
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
	auto powerUp = itemEntity.component<PowerUpComponent>();
	auto health = entity.component<HealthComponent>();

	if (powerUp && health)
	{
		auto effectBoost = powerUp->getEffectBoost();

		gameNode->schedule([entity, health, effectBoost](auto dt) mutable
		{
			if (entity.valid())
			{
				auto regenHealth = health->getCurrentHitpoints() + effectBoost;

				if (regenHealth <= health->getMaxHitpoints())
				{
					health->setCurrentHitpoints(regenHealth);
				}
			}
		}, 1.f, static_cast<int>(powerUp->getEffectTime()), 0.f, "Regen");
	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::Entity itemEntity)
{
	auto powerUp = itemEntity.component<PowerUpComponent>();
	auto speed = entity.component<SpeedComponent>();

	if (powerUp && speed)
	{
		auto originalSpeed = speed->getMaxSpeed();

		speed->setMaxSpeed(originalSpeed * (1 + powerUp->getEffectBoost()));

		gameNode->scheduleOnce([entity, speed, originalSpeed](auto dt) mutable
		{
			if (entity.valid())
			{
				speed->setMaxSpeed(originalSpeed);
			}
		}, powerUp->getEffectTime(), "reload");
	}
}