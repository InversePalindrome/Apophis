/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - PlayerSystem.cpp
InversePalindrome.com
*/


#pragma once

#include "Tags.hpp"
#include "Events.hpp"
#include "Constants.hpp"
#include "AppSettings.hpp"
#include "PlayerSystem.hpp"
#include "SteeringBehaviors.hpp"
#include "ConversionUtility.hpp"


PlayerSystem::PlayerSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager) :
	keyboardManager(keyboardManager),
	mouseManager(mouseManager)
{
}

void PlayerSystem::configure(entityx::EventManager& eventManager)
{
}

void PlayerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<Player> player;
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;

	for (auto entity : entityManager.entities_with_components(player, body, speed))
	{
		updateMovement(body, speed);
		updateRotation(body);
		updateShooting(eventManager, entity);
	}
}

void PlayerSystem::updateMovement(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed)
{
	const auto& appSettings = AppSettings::getInstance();

	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveRight)))
	{
		body->applyLinearImpulse(speed->getMaxLinearSpeed() * b2Vec2(1.f, 0.f));
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveLeft)))
	{
		body->applyLinearImpulse(speed->getMaxLinearSpeed() * b2Vec2(-1.f, 0.f));
	}
	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveUp)))
	{
		body->applyLinearImpulse(speed->getMaxLinearSpeed() * b2Vec2(0.f, 1.f));
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveDown)))
	{
		body->applyLinearImpulse(speed->getMaxLinearSpeed() * b2Vec2(0.f, -1.f));
	}
}

void PlayerSystem::updateRotation(entityx::ComponentHandle<BodyComponent> body)
{
	body->applyAngularImpulse(SteeringBehaviors::face(body->getPosition(), Utility::screenToWorldCoordinates(mouseManager->getMousePosition()), body->getAngle(), body->getAngularVelocity(), body->getInertia()));
}

void PlayerSystem::updateShooting(entityx::EventManager& eventManager, entityx::Entity player)
{
	if (mouseManager->isMousePressed())
	{
		eventManager.emit(ShootProjectile{ player,  Utility::screenToWorldCoordinates(mouseManager->getPosition()) });
	}
}