/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"

#include <beehive/beehive.hpp>

#include <entityx/System.h>


class StrikerSystem : public entityx::System<StrikerSystem>, public entityx::Receiver<StrikerSystem>
{
public:
	StrikerSystem();

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<BodyComponent> playerBody;

	beehive::Tree<entityx::Entity> strikerTree;

	void initStrikerTree();
};