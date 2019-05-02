/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "PatrolContext.hpp"

#include <entityx/Event.h>
#include <entityx/System.h>

#include <beehive/beehive.hpp>


class PatrolSystem : public entityx::System<PatrolSystem>, public entityx::Receiver<PatrolSystem>
{
public:
    PatrolSystem();

    virtual void configure(entityx::EventManager& eventManager) override;
    virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
    virtual void receive(const CrossedWaypoint& event);

private:
    beehive::Tree<PatrolContext> patrolTree;
};