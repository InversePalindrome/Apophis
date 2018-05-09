/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ItemSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "PowerUpComponent.hpp"

#include <entityx/System.h>

#include <cocos/2d/CCNode.h>


class ItemSystem : public entityx::System<ItemSystem>, public entityx::Receiver<ItemSystem>
{
public:
	explicit ItemSystem(cocos2d::Node* gameNode);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const TouchedPowerUp& event);

private:
	cocos2d::Node* gameNode;

	void addRegenBoost(entityx::Entity entity, entityx::ComponentHandle<PowerUpComponent> powerUp);
	void addSpeedBoost(entityx::Entity entity, entityx::ComponentHandle<PowerUpComponent> powerUp);
};