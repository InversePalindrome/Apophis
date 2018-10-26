/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "StrikerContext.hpp"
#include "TransformComponent.hpp"

#include <entityx/System.h>

#include <beehive/beehive.hpp>


class StrikerSystem : public entityx::System<StrikerSystem>, public entityx::Receiver<StrikerSystem>
{
public:
	explicit StrikerSystem(entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	beehive::Tree<StrikerContext> strikerTree;

	entityx::ComponentHandle<TransformComponent> playerTransform;
};