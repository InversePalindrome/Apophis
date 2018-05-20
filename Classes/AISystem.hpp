/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AISystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"

#include <beehive/beehive.hpp>

#include <entityx/System.h>


class AISystem : public entityx::System<AISystem>, public entityx::Receiver<AISystem>
{
public:
	AISystem();

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<BodyComponent> playerBody;

	beehive::Tree<entityx::Entity> strikerTree;
	beehive::Tree<entityx::Entity> patrollerTree;

	void initStrikerTree();
	void initPatrollerTree();
};