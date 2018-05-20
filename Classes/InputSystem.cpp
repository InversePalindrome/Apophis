/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - InputSystem.cpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "InputSystem.hpp"
#include "AppSettings.hpp"
#include "BodyComponent.hpp"


InputSystem::InputSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager) :
	keyboardManager(keyboardManager),
	mouseManager(mouseManager)
{
}

void InputSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<Player>>(*this);
}

void InputSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	if (player.valid())
	{
		handleKeyboard(eventManager);
		handleMouse(eventManager);
	}
}

void InputSystem::receive(const entityx::ComponentAddedEvent<Player>& event)
{
	player = event.entity;
}

void InputSystem::handleKeyboard(entityx::EventManager& eventManager)
{
	const auto& appSettings = AppSettings::getInstance();
	
	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveRight)))
	{
		eventManager.emit(MoveEntity{ player, {1.f, 0.f} });
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveLeft)))
	{
		eventManager.emit(MoveEntity{ player, {-1.f, 0.f} });
	}
	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveUp)))
	{
		eventManager.emit(MoveEntity{ player, {0.f, 1.f} });
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveDown)))
	{
		eventManager.emit(MoveEntity{ player, {0.f, -1.f} });
	}
}

void InputSystem::handleMouse(entityx::EventManager& eventManager)
{
	const auto& nodeMousePosition = mouseManager->convertToNodeSpace(mouseManager->getMousePosition());
	b2Vec2 worldMousePosition = { nodeMousePosition.x / PTM_RATIO, nodeMousePosition.y / PTM_RATIO };

	if (auto playerBody = player.component<BodyComponent>())
	{
		eventManager.emit(RotateEntity{ player, worldMousePosition - playerBody->getPosition() });
	}

	if (mouseManager->isMousePressed())
	{
		eventManager.emit(ShootProjectile{ player, worldMousePosition });
	}
}