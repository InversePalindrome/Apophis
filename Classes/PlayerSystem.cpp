/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - PlayerSystem.cpp
InversePalindrome.com
*/


#pragma once

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
    eventManager.subscribe<ComponentLoaded<ObjectComponent>>(*this);
}

void PlayerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
    if (player)
    {
        if (auto [body, speed, acceleration] = player.components<BodyComponent, SpeedComponent, AccelerationComponent>(); body && speed && acceleration)
        {
            updateMovement(body, speed, acceleration);
            updateRotation(body);
            updateShooting(eventManager);
        }
    }
}

void PlayerSystem::receive(const ComponentLoaded<ObjectComponent>& event)
{
    if (event.component->getObjectType() == +ObjectType::Player)
    {
        player = event.entity;
    }
}

void PlayerSystem::updateMovement(entityx::ComponentHandle<BodyComponent> body, const entityx::ComponentHandle<SpeedComponent> speed, const entityx::ComponentHandle<AccelerationComponent> acceleration)
{
    for (auto keyAction : keyActions)
    {
        switch (keyAction)
        {
        case KeyAction::MoveRight:
            body->applyLinearImpulse({ body->getMass() * (b2Min(body->getLinearVelocity().x + acceleration->getLinearAcceleration(), speed->getMaxLinearSpeed()) - body->getLinearVelocity().x), 0.f });
            break;
        case KeyAction::MoveLeft:
            body->applyLinearImpulse({ body->getMass() * (b2Max(body->getLinearVelocity().x - acceleration->getLinearAcceleration(), -speed->getMaxLinearSpeed()) - body->getLinearVelocity().x), 0.f });
            break;
        case KeyAction::MoveUp:
            body->applyLinearImpulse({ 0.f, body->getMass() * (b2Min(body->getLinearVelocity().y + acceleration->getLinearAcceleration(), speed->getMaxLinearSpeed()) - body->getLinearVelocity().y) });
            break;
        case KeyAction::MoveDown:
            body->applyLinearImpulse({ 0.f, body->getMass() * (b2Max(body->getLinearVelocity().y - acceleration->getLinearAcceleration(), -speed->getMaxLinearSpeed()) - body->getLinearVelocity().y) });
            break;
        }
    }
}

void PlayerSystem::updateRotation(entityx::ComponentHandle<BodyComponent> body)
{
    body->applyAngularImpulse(SteeringBehaviors::face(body->getPosition(), { playerFocusPoint.x / Constants::PTM_RATIO, playerFocusPoint.y / Constants::PTM_RATIO }, body->getAngle(), body->getAngularVelocity(), body->getInertia()));
}

void PlayerSystem::updateShooting(entityx::EventManager& eventManager)
{
    if (isShooting)
    {
        eventManager.emit(ShootProjectile{ player });
    }
}