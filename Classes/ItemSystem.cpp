/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "SpeedComponent.hpp"
#include "HitpointComponent.hpp"


ItemSystem::ItemSystem(cocos2d::Node* gameNode) :
	gameNode(gameNode)
{
}

void ItemSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<TouchedPowerUp>(*this);
}

void ItemSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{

}

void ItemSystem::receive(const TouchedPowerUp& event)
{
	if (auto powerUp = event.powerUp.component<PowerUpComponent>())
	{
		switch (powerUp->getPowerUpType())
		{
		case PowerUpType::Regen:
			addRegenBoost(event.entity, powerUp);
			break;
		case PowerUpType::Speed:
			addSpeedBoost(event.entity, powerUp);
			break;
		}
	}
}

void ItemSystem::addRegenBoost(entityx::Entity entity, entityx::ComponentHandle<PowerUpComponent> powerUp)
{
	if (auto health = entity.component<HealthComponent>())
	{

	}
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, entityx::ComponentHandle<PowerUpComponent> powerUp)
{
	if (auto speed = entity.component<SpeedComponent>())
	{
		auto originalSpeed = speed->getMaxSpeed();

		speed->setMaxSpeed(speed->getMaxSpeed() + speed->getMaxSpeed() * powerUp->getEffectBoost());

		gameNode->scheduleOnce([speed, originalSpeed](auto dt) mutable
		{
			speed->setMaxSpeed(originalSpeed);
		}, powerUp->getEffectTime(), "reload");
	}
}