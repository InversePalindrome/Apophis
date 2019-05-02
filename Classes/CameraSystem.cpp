/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CameraSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "CameraSystem.hpp"
#include "ObjectComponent.hpp"

#include <cocos/base/CCDirector.h>


CameraSystem::CameraSystem(cocos2d::Node* gameNode, const b2Vec2& mapDimensions) :
    gameNode(gameNode),
    mapDimensions(mapDimensions)
{
}

void CameraSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<EntityParsed>(*this);
}

void CameraSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
    if (playerTransform)
    {
        const auto playerNodePosition = cocos2d::Vec2(playerTransform->getPosition().x * Constants::PTM_RATIO, playerTransform->getPosition().y * Constants::PTM_RATIO);
        const auto worldPoint = gameNode->convertToWorldSpace(playerNodePosition);
        const auto windowSize = cocos2d::Director::getInstance()->getWinSize();

        if (std::abs(playerNodePosition.x) < mapDimensions.x * Constants::PTM_RATIO / 2.f - windowSize.width / 2.f)
        {
            gameNode->setPositionX(gameNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
        }
        if (std::abs(playerNodePosition.y) < mapDimensions.y * Constants::PTM_RATIO / 2.f - windowSize.height / 2.f)
        {
            gameNode->setPositionY(gameNode->getPosition().y - worldPoint.y + windowSize.height / 2.f);
        }
    }
}

void CameraSystem::receive(const EntityParsed & event)
{
    if (const auto [object, transform] = event.entity.components<ObjectComponent, TransformComponent>();
        object && transform && object->getObjectType() == +ObjectType::Player)
    {
        playerTransform = transform;
    }
}