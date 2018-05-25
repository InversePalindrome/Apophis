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


PlayerSystem::PlayerSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager) :
	keyboardManager(keyboardManager),
	mouseManager(mouseManager)
{
}

void PlayerSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<Player>>(*this);
}

void PlayerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	if (player.valid())
	{
		handleMovement(eventManager);
		handleRotation(eventManager);
	}
}

void PlayerSystem::receive(const entityx::ComponentAddedEvent<Player>& event)
{
	player = event.entity;
}

void PlayerSystem::handleMovement(entityx::EventManager& eventManager)
{
	const auto& appSettings = AppSettings::getInstance();

	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveRight)))
	{
		eventManager.emit(ApplyLinearImpulse{ player, {1.f, 0.f} });
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveLeft)))
	{
		eventManager.emit(ApplyLinearImpulse{ player, {-1.f, 0.f } });
	}
	if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveUp)))
	{
		eventManager.emit(ApplyLinearImpulse{ player, {0.f, 1.f} });
	}
	else if (keyboardManager->isKeyPressed(appSettings.getKeyCode(KeyAction::MoveDown)))
	{
		eventManager.emit(ApplyLinearImpulse{ player, {0.f, -1.f} });
	}
}

void PlayerSystem::handleRotation(entityx::EventManager& eventManager)
{
	cocos2d::Vec2 nodeMousePosition(mouseManager->convertToNodeSpace(mouseManager->getMousePosition()));
	b2Vec2 worldMousePosition(nodeMousePosition.x / Constants::PTM_RATIO, nodeMousePosition.y / Constants::PTM_RATIO);

	eventManager.emit(Face{ player, worldMousePosition });

	if (mouseManager->isMousePressed())
	{
		eventManager.emit(ShootProjectile{ player, worldMousePosition });
	}
}