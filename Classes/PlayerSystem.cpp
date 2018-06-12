/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - PlayerSystem.cpp
InversePalindrome.com
*/


#pragma once

#include "Tags.hpp"
#include "Events.hpp"
#include "Vector2.hpp"
#include "Constants.hpp"
#include "AppSettings.hpp"
#include "PlayerSystem.hpp"
#include "SteeringBehaviors.hpp"


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
	entityx::ComponentHandle<SpeedComponent> speed;
	entityx::ComponentHandle<ImpulseComponent> impulse;
	entityx::ComponentHandle<BodyComponent> body;

	for (auto entity : entityManager.entities_with_components(player, speed, impulse, body))
	{
		updateMovement(speed, impulse);
		updateRotation(impulse, body);
		updateShooting(eventManager, entity);
	}
}

void PlayerSystem::updateMovement(entityx::ComponentHandle<SpeedComponent> speed, entityx::ComponentHandle<ImpulseComponent> impulse)
{
	const auto& appSettings = AppSettings::getInstance();

	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveRight)))
	{
		impulse += speed->getMaxLinearSpeed() * b2Vec2(1.f, 0.f);
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveLeft)))
	{
		impulse += speed->getMaxLinearSpeed() * b2Vec2(-1.f, 0.f);
	}
	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveUp)))
	{
		impulse += speed->getMaxLinearSpeed() * b2Vec2(0.f, 1.f);
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveDown)))
	{
		impulse += speed->getMaxLinearSpeed() * b2Vec2(0.f, -1.f);
	}
}

void PlayerSystem::updateRotation(entityx::ComponentHandle<ImpulseComponent> impulse, entityx::ComponentHandle<BodyComponent> body)
{
	impulse += SteeringBehaviors::face(body->getPosition(), { mouseManager->getMousePosition().x / Constants::PTM_RATIO, mouseManager->getMousePosition().y / Constants::PTM_RATIO }, body->getAngle(), body->getAngularVelocity(), body->getInertia());
}

void PlayerSystem::updateShooting(entityx::EventManager& eventManager, entityx::Entity player)
{
	if (mouseManager->isMousePressed())
	{
		eventManager.emit(ShootProjectile{ player,  Vector2f{mouseManager->getMousePosition().x / Constants::PTM_RATIO, mouseManager->getMousePosition().y / Constants::PTM_RATIO} });
	}
}