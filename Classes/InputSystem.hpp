/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - InputSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Tags.hpp"
#include "MouseManager.hpp"
#include "KeyboardManager.hpp"

#include <entityx/System.h>


class InputSystem : public entityx::System<InputSystem>, public entityx::Receiver<InputSystem>
{
public:
	InputSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::ComponentAddedEvent<Player>& event);

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	entityx::Entity player;

	void handleKeyboard(entityx::EventManager& eventManager);
	void handleMouse(entityx::EventManager& eventManager);
};