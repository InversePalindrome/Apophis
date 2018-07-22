/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "WanderComponent.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"
#include "TransformComponent.hpp"

#include <entityx/System.h>

#include <beehive/beehive.hpp>


struct StrikerContext
{
	entityx::Entity striker;
	BodyComponent& body;
	const SpeedComponent& speed;
	WanderComponent& wander;
	const VisionComponent& vision;
	const HealthComponent& health;
};

class StrikerSystem : public entityx::System<StrikerSystem>, public entityx::Receiver<StrikerSystem>
{
public:
	StrikerSystem();

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<TransformComponent> playerTransform;

	beehive::Tree<StrikerContext> strikerTree;
};