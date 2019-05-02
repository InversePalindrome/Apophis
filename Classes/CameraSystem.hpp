/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CameraSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "TransformComponent.hpp"

#include <cocos/2d/CCNode.h>

#include <entityx/System.h>


class CameraSystem : public entityx::System<CameraSystem>, public entityx::Receiver<CameraSystem>
{
public:
    CameraSystem(cocos2d::Node* gameNode, const b2Vec2& mapDimensions);

    virtual void configure(entityx::EventManager& eventManager) override;
    virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
    virtual void receive(const EntityParsed& event);

private:
    cocos2d::Node* gameNode;
    const b2Vec2& mapDimensions;

    entityx::ComponentHandle<TransformComponent> playerTransform;
};