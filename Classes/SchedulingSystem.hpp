/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SchedulingSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <entityx/System.h>


class SchedulingSystem : public entityx::System<SchedulingSystem>, public entityx::Receiver<SchedulingSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const ScheduleOnce& event);
	virtual void receive(const Schedule& event);
	virtual void receive(const Unschedule& event);
};