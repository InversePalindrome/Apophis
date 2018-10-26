/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "DroneContext.hpp"

#include <entityx/Entity.h>
#include <entityx/System.h>

#include <beehive/beehive.hpp>


class DroneSystem : public entityx::System<DroneSystem>, public entityx::Receiver<DroneSystem>
{
public:
	DroneSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	beehive::Tree<DroneContext> droneTree;
};