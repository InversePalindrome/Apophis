/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"
#include "CollisionFilter.hpp"
#include "CollisionManager.hpp"
#include "DistanceJointComponent.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <entityx/System.h> 

#include <vector>
#include <functional>


class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
public:
	PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const entityx::ComponentRemovedEvent<BodyComponent>& event);
	virtual void receive(const entityx::ComponentRemovedEvent<DistanceJointComponent>& event);
	virtual void receive(const EntityParsed& event);
	virtual void receive(const CreateBody& event);
	virtual void receive(const CreateJoint<DistanceJointComponent>& event);

private:
	b2World world;
	CollisionManager collisionManager;
	CollisionFilter collisionFilter;

	std::vector<std::function<void()>> worldCallbacks;

	entityx::EntityManager& entityManager;

	void updateWorldCallbacks();

	template<typename TJoint, typename TJointDef>
	void createJoint(entityx::Entity entity, TJointDef jointDef);

	void destroyBody(b2Body* body);
	void destroyJoint(b2Joint* joint);
};


template<typename TJoint, typename TJointDef>
void PhysicsSystem::createJoint(entityx::Entity entity, TJointDef jointDef)
{
	auto createJoint = [this, entity, jointDef]() mutable { entity.assign<TJoint>(world.CreateJoint(&jointDef)); };

	if (world.IsLocked())
	{
		worldCallbacks.push_back(createJoint);
	}
	else
	{
		createJoint();
	}
}