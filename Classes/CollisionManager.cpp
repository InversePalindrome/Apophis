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

void CollisionManager::update()
{
	for (const auto& collisionCallback : collisionCallbacks)
	{
		collisionCallback();
	}
	
	collisionCallbacks.clear();
}

void CollisionManager::BeginContact(b2Contact* contact)
{
	auto* entityA = static_cast<entityx::Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto* entityB = static_cast<entityx::Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	collisionCallbacks.push_back([this, entityA, entityB]()
	{
		if (entityA && entityB && *entityA && *entityB)
		{
			if (auto collisionPair = getCollisionPair(entityA, entityB, ObjectType::Projectile, ObjectType::Alive))
			{
				eventManager.emit(CombatOcurred{ collisionPair->first, collisionPair->second });

				collisionPair->first.destroy();
			}
			else if (auto collisionPair = getCollisionPair(entityA, entityB, ObjectType::Player, ObjectType::Item))
			{
				eventManager.emit(PickedUpItem{ collisionPair->first, collisionPair->second });
			}
			else if (auto collisionPair = getCollisionPair(entityA, entityB, ObjectType::Patrol, ObjectType::Path))
			{
				eventManager.emit(CrossedWaypoint{ collisionPair->first, collisionPair->second });
			}
		}
	});
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
CollisionManager::getCollisionPair(entityx::Entity* entityA, entityx::Entity* entityB, ObjectType objectTypeA, ObjectType objectTypeB)
{
	if (const auto objectA = entityA->component<ObjectComponent>(),
		objectB = entityB->component<ObjectComponent>();
	    objectA && objectB)
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