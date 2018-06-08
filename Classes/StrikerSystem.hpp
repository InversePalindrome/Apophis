/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Tags.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "WanderComponent.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"

#include <beehive/beehive.hpp>

#include <entityx/System.h>


struct StrikerContext
{
	entityx::Entity striker;
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;
	entityx::ComponentHandle<WanderComponent> wander;
	entityx::ComponentHandle<VisionComponent> vision;
	entityx::ComponentHandle<HealthComponent> health;
};

class StrikerSystem : public entityx::System<StrikerSystem>, public entityx::Receiver<StrikerSystem>
{
public:
	StrikerSystem();

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::ComponentAddedEvent<Player>& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<BodyComponent> playerBody;

	beehive::Tree<StrikerContext> strikerTree;
};