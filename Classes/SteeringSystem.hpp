/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"

#include <entityx/entityx.h>


class SteeringSystem : public entityx::System<SteeringSystem>, public entityx::Receiver<SteeringSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityCreated& event);

private:
	entityx::ComponentHandle<BodyComponent> playerBody;
};