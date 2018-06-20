/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "CollisionFilter.hpp"
#include "CollisionManager.hpp"
#include "ImpulseComponent.hpp"
#include "GeometryComponent.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <entityx/System.h>

#include <vector>


class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
public:
	PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const entityx::ComponentAddedEvent<BodyComponent>& event);
	virtual void receive(const entityx::ComponentRemovedEvent<BodyComponent>& event);
	virtual void receive(const CreateDistanceJoint& event);

private:
	b2World world;
	CollisionManager collisionManager;
	CollisionFilter collisionFilter;

	entityx::EntityManager& entityManager;

	std::vector<std::pair<entityx::Entity, entityx::ComponentHandle<BodyComponent>>> bodiesToCreate;
	std::vector<b2Body*> bodiesToRemove;

	void updateWorld();

	void createBodies();
	void removeBodies();

	static void updateSpatialProperties(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<GeometryComponent> geometry);
	static void applyImpulses(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<ImpulseComponent> impulse);
	static void limitLinearSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed);
	static void limitAngularSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed);
};