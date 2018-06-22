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

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerMouse.h>
#include <cocos/base/CCEventListenerKeyboard.h>


PlayerSystem::PlayerSystem(cocos2d::Node* gameNode) :
	gameNode(gameNode),
	isShooting(false)
{
	const auto& appSettings = AppSettings::getInstance();

	auto* keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [this, &appSettings](auto keyCode, auto* event) 
	{ 
		if (appSettings.hasKeyAction(keyCode))
		{
			keyActions.push_back(appSettings.getKeyAction(keyCode));
		}
	};
	keyboardListener->onKeyReleased = [this, &appSettings](auto keyCode, auto* event) 
	{
		if (appSettings.hasKeyAction(keyCode))
		{
			keyActions.erase(std::remove(std::begin(keyActions), std::end(keyActions), appSettings.getKeyAction(keyCode)), std::end(keyActions));
		}
	};

	auto* mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseMove = [this, gameNode](auto* event) { playerFocusPoint = gameNode->convertToNodeSpace({ event->getCursorX(), event->getCursorY() }); };
	mouseListener->onMouseDown = [this](auto* event) { isShooting = true; };
	mouseListener->onMouseUp = [this](auto* event) { isShooting = false; };

	gameNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, gameNode);
	gameNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, gameNode);
}

void PlayerSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;
	 
	eventManager.subscribe<EntityParsed>(*this);
}

void PlayerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	updateMovement();
	updateRotation();
	updateShooting();
}

void PlayerSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		player = event.entity;
		playerBody = event.entity.component<BodyComponent>();
		playerSpeed = event.entity.component<SpeedComponent>();
		playerImpulse = event.entity.component<ImpulseComponent>();
	}
}

void PlayerSystem::updateMovement()
{
	if (playerSpeed && playerImpulse)
	{
		for (const auto& keyAction : keyActions)
		{
			switch (keyAction)
			{
			case KeyAction::MoveRight:
				playerImpulse += playerSpeed->getMaxLinearSpeed() * b2Vec2(1.f, 0.f);
				break;
			case KeyAction::MoveLeft:
				playerImpulse += playerSpeed->getMaxLinearSpeed() * b2Vec2(-1.f, 0.f);
				break;
			case KeyAction::MoveUp:
				playerImpulse += playerSpeed->getMaxLinearSpeed() * b2Vec2(0.f, 1.f);
				break;
			case KeyAction::MoveDown:
				playerImpulse += playerSpeed->getMaxLinearSpeed() * b2Vec2(0.f, -1.f);
				break;
			}
		}
	}
}

void PlayerSystem::updateRotation()
{
	if (playerImpulse && playerBody && playerBody->getBody())
	{
		playerImpulse += SteeringBehaviors::face(playerBody->getPosition(), { playerFocusPoint.x / Constants::PTM_RATIO, playerFocusPoint.y / Constants::PTM_RATIO }, playerBody->getAngle(), playerBody->getAngularVelocity(), playerBody->getInertia());
	}
}

void PlayerSystem::updateShooting()
{
	if (player && isShooting)
	{
		eventManager->emit(ShootProjectile{ player });
	}
}