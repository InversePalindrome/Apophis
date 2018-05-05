/*
Copyright (c) 2018 Inverse Palindrome
JATR66  - InputSystem.cpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "InputSystem.hpp"
#include "AppSettings.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "PhysicsUtility.hpp"


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
	auto body = player.component<BodyComponent>();
	auto speed = player.component<SpeedComponent>();

	if (body && speed)
	{
		auto& appSettings = AppSettings::getInstance();

		b2Vec2 velocity(0.f, 0.f);

		if (keyboardManager->isKeyPressed(appSettings.getKeyCode("Move Right")))
		{
			velocity.x += speed->getMaxSpeed();
		}
		else if (keyboardManager->isKeyPressed(appSettings.getKeyCode("Move Left")))
		{
			velocity.x -= speed->getMaxSpeed();
		}
		if (keyboardManager->isKeyPressed(appSettings.getKeyCode("Move Up")))
		{
			velocity.y += speed->getMaxSpeed();
		}
		else if (keyboardManager->isKeyPressed(appSettings.getKeyCode("Move Down")))
		{
			velocity.y -= speed->getMaxSpeed();
		}
	
		eventManager.emit(ApplyLinearImpulse{ player, velocity - body->getLinearVelocity() });
	}
}

void InputSystem::handleMouse(entityx::EventManager& eventManager)
{
	if (auto body = player.component<BodyComponent>())
	{
		const auto& nodeMousePosition = mouseManager->convertToNodeSpace(mouseManager->getMousePosition());
		b2Vec2 worldMousePosition = { nodeMousePosition.x / PTM_RATIO, nodeMousePosition.y / PTM_RATIO };

		eventManager.emit(ApplyAngularImpulse{ player, Utility::angularImpulseToAngle(body->getAngle(), Utility::vectorToRadian(worldMousePosition - body->getPosition()), body->getAngularVelocity(), body->getInertia()) });

		if (mouseManager->isMousePressed())
		{
			eventManager.emit(ShootProjectile{ player, worldMousePosition });
		}
	}
}