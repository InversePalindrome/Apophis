/*
Copyright (c) 2018 Inverse Palindrome
Apophis - CollisionManager.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "ObjectComponent.hpp"
#include "CollisionManager.hpp"

#include <Box2D/Dynamics/b2Fixture.h>

#include <any>


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
	const auto* bodyA = contact->GetFixtureA()->GetBody();
	const auto* bodyB = contact->GetFixtureB()->GetBody();

	collisionCallbacks.push_back([this, bodyA, bodyB]()
	{
		if (!bodyA || !bodyB)
		{
			return;
		}

		if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Projectile, ObjectType::Alive))
		{
			eventManager.emit(CombatOcurred{ collisionPair->first, collisionPair->second });

			collisionPair->first.destroy();
		}
		else if (auto collisionPair = getCollisionPair(bodyA, bodyB, ObjectType::Player, ObjectType::Item))
		{
			eventManager.emit(PickedUpItem{ collisionPair->first, collisionPair->second });
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
CollisionManager::getCollisionPair(const b2Body* bodyA, const b2Body* bodyB, ObjectType objectTypeA, ObjectType objectTypeB)
{
    auto* userDataA = static_cast<std::any*>(bodyA->GetUserData());
	auto* userDataB = static_cast<std::any*>(bodyB->GetUserData());

	if (userDataA->type() == typeid(entityx::Entity) && userDataB->type() == typeid(entityx::Entity))
	{
		auto* entityA = std::any_cast<entityx::Entity>(userDataA);
	    auto* entityB = std::any_cast<entityx::Entity>(userDataB);

		if (*entityA && *entityB)
		{
			const auto objectA = entityA->component<ObjectComponent>();
			const auto objectB = entityB->component<ObjectComponent>();

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
		}
	}

	return {};
}