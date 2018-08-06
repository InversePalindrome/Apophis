/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <entityx/Entity.h>
#include <entityx/System.h>

#include <cpptime.h>


class CombatSystem : public entityx::System<CombatSystem>, public entityx::Receiver<CombatSystem>
{
public:
    CombatSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const ShootProjectile& event);
	virtual void receive(const CombatOcurred& event);

private:
	entityx::EntityManager& entityManager;
	entityx::EventManager& eventManager;

	CppTime::Timer timer;

	void handleExplosion(entityx::Entity destroyedEntity);
};