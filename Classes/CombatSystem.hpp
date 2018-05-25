/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CombatSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "EntityParser.hpp"

#include <entityx/System.h>


class CombatSystem : public entityx::System<CombatSystem>, public entityx::Receiver<CombatSystem>
{
public:
	explicit CombatSystem(EntityParser& entityParser);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const ShootProjectile& event);
	virtual void receive(const EntityDied& event);
	virtual void receive(const ProjectileHit& event);

private:
	EntityParser& entityParser;
	entityx::EventManager* eventManager;
};