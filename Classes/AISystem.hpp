/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AISystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"
#include "BehaviorTreeComponent.hpp"

#include <entityx/System.h>


class AISystem : public entityx::System<AISystem>, public entityx::Receiver<AISystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityCreated& event);
	virtual void receive(const entityx::ComponentAddedEvent<BehaviorTreeComponent>& event);

private:
	entityx::EventManager* eventManager;
	entityx::ComponentHandle<BodyComponent> playerBody;
};