/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CombatSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "EntityFactory.hpp"

#include <entityx/entityx.h>

#include <cocos/2d/CCNode.h>


class CombatSystem : public entityx::System<CombatSystem>, public entityx::Receiver<CombatSystem>
{
public:
	CombatSystem(cocos2d::Node* gameNode, EntityFactory& entityFactory);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityDied& event);
	virtual void receive(const ShootProjectile& event);
	virtual void receive(const ProjectileHit& event);

private:
	cocos2d::Node* gameNode;

	EntityFactory& entityFactory;
	entityx::EventManager* eventManager;
};