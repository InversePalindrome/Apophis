/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SchedulingSystem.cpp
InversePalindrome.com
*/


#include "NodeComponent.hpp"
#include "SchedulingSystem.hpp"


void SchedulingSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<ScheduleOnce>(*this);
	eventManager.subscribe<Schedule>(*this);
	eventManager.subscribe<Unschedule>(*this);
}

void SchedulingSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{

}

void SchedulingSystem::receive(const ScheduleOnce& event)
{
	if (auto node = event.entity.component<NodeComponent>())
	{
		node->scheduleOnce(event.callback, event.delay, event.key);
	}
}

void SchedulingSystem::receive(const Schedule& event)
{
	if (auto node = event.entity.component<NodeComponent>())
	{
		node->schedule(event.callback, event.interval, event.repeat, event.delay, event.key);
	}
}

void SchedulingSystem::receive(const Unschedule& event)
{
	if (auto node = event.entity.component<NodeComponent>())
	{
		node->unschedule(event.key);
	}
}