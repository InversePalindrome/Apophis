/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CollisionManager.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <vector>
#include <utility>
#include <optional>
#include <functional>


class CollisionManager : public b2ContactListener
{
public:
    explicit CollisionManager(entityx::EventManager& eventManager);
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator= (const CollisionManager&) = delete;

    void update();

private:
    entityx::EventManager& eventManager;

    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

    std::optional<std::pair<entityx::Entity, entityx::Entity>>
        getCollisionPair(entityx::Entity* entityA, entityx::Entity* entityB, ObjectType objectTypeA, ObjectType objectTypeB);

    std::vector<std::function<void()>> collisionCallbacks;
};