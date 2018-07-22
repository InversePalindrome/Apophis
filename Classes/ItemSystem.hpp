/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "EntityFactory.hpp"
#include "WeaponComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"

#include <entityx/System.h>

#include <cpptime.h>

#include <random>


class ItemSystem : public entityx::System<ItemSystem>, public entityx::Receiver<ItemSystem>
{
public:
	explicit ItemSystem(EntityFactory& entityFactory);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const PickedUpItem& event);

private:
	EntityFactory& entityFactory;

	CppTime::Timer timer;

	std::mt19937 randomEngine;

	static void addWeapon(entityx::Entity entity, entityx::ComponentHandle<WeaponComponent> weapon);
	void addRegenBoost(entityx::Entity entity, const entityx::ComponentHandle<RegenBoostComponent> regenBoost);
	void addSpeedBoost(entityx::Entity entity, const entityx::ComponentHandle<SpeedBoostComponent> speedBoost);
};