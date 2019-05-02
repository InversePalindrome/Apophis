/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "DroneContext.hpp"

#include <entityx/Entity.h>
#include <entityx/System.h>

#include <beehive/beehive.hpp>


class DroneSystem : public entityx::System<DroneSystem>
{
public:
    DroneSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

    virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
    beehive::Tree<DroneContext> droneTree;
};