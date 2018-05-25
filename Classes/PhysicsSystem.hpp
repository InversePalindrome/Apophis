/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "CollisionManager.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <entityx/System.h>


class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
public:
    PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const entityx::ComponentRemovedEvent<BodyComponent>& event);
	virtual void receive(const CreateBody& event);
	virtual void receive(const CreateDistanceJoint& event);
	virtual void receive(const RayCast& event);
	virtual void receive(const QueryAABB& event);
	virtual void receive(const SetBodyPosition& event);
	virtual void receive(const SetBodyAngle& event);
	virtual void receive(const SetLinearVelocity& event);
	virtual void receive(const SetAngularVelocity& event);
	virtual void receive(const ApplyLinearImpulse& event);
	virtual void receive(const ApplyAngularImpulse& event);
	virtual void receive(const ApplyLinearForce& event);
	virtual void receive(const ApplyRotationalForce& event);

private:
	b2World world;
	CollisionManager collisionManager;
	
	entityx::EntityManager& entityManager;

	void updateWorld();

	void limitLinearSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed);
	void limitAngularSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed);
};