/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Tags.hpp"
#include "MouseManager.hpp"
#include "KeyboardManager.hpp"

#include <entityx/System.h>


class PlayerSystem : public entityx::System<PlayerSystem>, public entityx::Receiver<PlayerSystem>
{
public:
	PlayerSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::ComponentAddedEvent<Player>& event);

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	entityx::Entity player;

	void handleMovement(entityx::EventManager& eventManager);
	void handleRotation(entityx::EventManager& eventManager);
};