/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CollisionManager.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <entityx/entityx.h>

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <cocos/2d/CCNode.h>

#include <utility>
#include <optional>


class CollisionManager : public b2ContactListener
{
public:
	CollisionManager(cocos2d::Node* mainNode, entityx::EventManager& eventManager);
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator= (const CollisionManager&) = delete;

private:
	cocos2d::Node* mainNode;
	entityx::EventManager& eventManager;

	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

	std::optional<std::pair<entityx::Entity, entityx::Entity>>
    getCollisionPair(const b2Body* bodyA, const b2Body* bodyB, ObjectType objectTypeA, ObjectType objectTypeB);
};