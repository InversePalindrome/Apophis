/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - CollisionManager.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "BodyComponent.hpp"
#include "CollisionManager.hpp"

#include <Box2D/Dynamics/b2Fixture.h>


CollisionManager::CollisionManager(cocos2d::Node* gameNode, entityx::EventManager& eventManager) :
	gameNode(gameNode),
	eventManager(eventManager)
{
}

void CollisionManager::BeginContact(b2Contact* contact)
{
	const auto* bodyA = contact->GetFixtureA()->GetBody();
	const auto* bodyB = contact->GetFixtureB()->GetBody();

	if (!bodyA || !bodyB)
	{
		return;
	}

	gameNode->scheduleOnce([this, bodyA, bodyB](auto dt) 
	{
		if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Projectile, ObjectType::Alive))
		{
			eventManager.emit(CombatOcurred{ collisionPair->first, collisionPair->second });
			collisionPair->first.destroy();
		}
		else if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Player, ObjectType::PowerUp))
		{
			eventManager.emit(TouchedPowerUp{ collisionPair->first, collisionPair->second });
			collisionPair->second.destroy();
		}
	}, 0.f, "CollisionStarted");
}

void CollisionManager::EndContact(b2Contact* contact)
{

}

void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

std::optional<std::pair<entityx::Entity, entityx::Entity>>
CollisionManager::getCollisionPair(const b2Body* bodyA, const b2Body* bodyB, ObjectType objectTypeA, ObjectType objectTypeB)
{
	const auto* bodyDataA = static_cast<BodyData*>(bodyA->GetUserData());
	const auto* bodyDataB = static_cast<BodyData*>(bodyB->GetUserData());

	if (bodyDataA && bodyDataB)
	{
		if (bodyDataA->objectType & objectTypeA && bodyDataB->objectType & objectTypeB)
		{
			return { {bodyDataA->entity, bodyDataB->entity} };
		}
		else if (bodyDataA->objectType & objectTypeB && bodyDataB->objectType & objectTypeA)
		{
			return { {bodyDataB->entity, bodyDataA->entity} };
		}
	}

	return {};
}