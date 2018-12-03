/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StateSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "StateComponent.hpp"

#include <entityx/System.h>


class StateSystem : public entityx::System<StateSystem>, public entityx::Receiver<StateSystem>
{
public:
	explicit StateSystem(entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const ComponentLoaded<StateComponent>& event);
	virtual void receive(const ChangeState& event);

private:
	entityx::EventManager& eventManager;
};