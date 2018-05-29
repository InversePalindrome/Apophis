/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <entityx/System.h>


class SteeringSystem : public entityx::System<SteeringSystem>, public entityx::Receiver<SteeringSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const Seek& event);
	virtual void receive(const Flee& event);
	virtual void receive(const Pursue& event);
	virtual void receive(const Evade& event);
	virtual void receive(const Arrive& event);
	virtual void receive(const Follow& event);
	virtual void receive(const Wander& event);
	virtual void receive(const Avoid& event);
	virtual void receive(const Orbit& event);
	virtual void receive(const Align& event);
	virtual void receive(const Cohesion& event);
	virtual void receive(const Separate& event);
	virtual void receive(const Queue& event);
	virtual void receive(const Face& event);

private:
	entityx::EventManager* eventManager;
};