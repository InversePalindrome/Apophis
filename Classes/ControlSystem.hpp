/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ControlSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "EntityParser.hpp"

#include <entityx/System.h>


class ControlSystem : public entityx::System<ControlSystem>, public entityx::Receiver<ControlSystem>
{
public:
	explicit ControlSystem(EntityParser& entityParser);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const MoveEntity& event);
	virtual void receive(const RotateEntity& event);
	virtual void receive(const ShootProjectile& event);

private:
	EntityParser& entityParser;
	entityx::EventManager* eventManager;
};