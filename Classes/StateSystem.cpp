/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StateSystem.cpp
InversePalindrome.com
*/


#include "StateSystem.hpp"


StateSystem::StateSystem(entityx::EventManager& eventManager) :
    eventManager(eventManager)
{
}

void StateSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<ComponentLoaded<StateComponent>>(*this);
    eventManager.subscribe<ChangeState>(*this);
}

void StateSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{

}

void StateSystem::receive(const ComponentLoaded<StateComponent>& event)
{
    eventManager.emit(ChangeState{ event.entity, event.component->getState() });
}

void StateSystem::receive(const ChangeState& event)
{
    if (auto state = event.entity.component<StateComponent>())
    {
        state->setState(event.state);

        eventManager.emit(StateChanged{ event.entity, event.state });
    }
}