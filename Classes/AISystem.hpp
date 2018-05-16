/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AISystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"

#include <entityx/System.h>

#include <beehive/beehive.hpp>


class AISystem : public entityx::System<AISystem>, public entityx::Receiver<AISystem>
{
public:
	AISystem();

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityCreated& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<BodyComponent> playerBody;

	beehive::Tree<entityx::Entity> strikerTree;
	beehive::Tree<entityx::Entity> patrollerTree;

	void initStrikerTree();
	void initPatrollerTree();
};