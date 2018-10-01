/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "DroneContext.hpp"
#include "TransformComponent.hpp"

#include <entityx/Event.h>
#include <entityx/System.h>

#include <beehive/beehive.hpp>


class DroneSystem : public entityx::System<DroneSystem>, public entityx::Receiver<DroneSystem>
{
public:
	explicit DroneSystem(entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	entityx::EventManager& eventManager;

	beehive::Tree<DroneContext> droneTree;

	entityx::ComponentHandle<TransformComponent> playerTransform;
};