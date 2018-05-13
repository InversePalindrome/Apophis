/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ControlSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "EntityFactory.hpp"

#include <entityx/System.h>

#include <cocos/2d/CCNode.h>


class ControlSystem : public entityx::System<ControlSystem>, public entityx::Receiver<ControlSystem>
{
public:
	ControlSystem(cocos2d::Node* gameNode, EntityFactory& enityFactory);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const MoveEntity& event);
	virtual void receive(const RotateEntity& event);
	virtual void receive(const ShootProjectile& event);

private:
	cocos2d::Node* gameNode;

	EntityFactory& entityFactory;
	entityx::EventManager* eventManager;
};