/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CollisionManager.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "ObjectComponent.hpp"
#include "CollisionManager.hpp"

#include <Box2D/Dynamics/b2Fixture.h>


CollisionManager::CollisionManager(entityx::EventManager& eventManager) :
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

	if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Projectile, ObjectType::Alive))
	{
		//eventManager.emit(ProjectileHit{ collisionPair->first, collisionPair->second });
	}
	else if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Player, ObjectType::Item))
	{
		eventManager.emit(PickedUpItem{ collisionPair->first, collisionPair->second });
	}
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
	auto* entityA = static_cast<entityx::Entity*>(bodyA->GetUserData());
	auto* entityB = static_cast<entityx::Entity*>(bodyB->GetUserData());

	auto objectA = entityA->component<ObjectComponent>();
	auto objectB = entityB->component<ObjectComponent>();
		
	if (objectA && objectB)
	{
		if (objectA->getObjectType() & objectTypeA && objectB->getObjectType() & objectTypeB)
		{
			return { { *entityA, *entityB } };
		}
		else if (objectA->getObjectType() & objectTypeB && objectB->getObjectType() & objectTypeA)
		{
			return { { *entityB, *entityA } };
		}
	}

	return {};
}