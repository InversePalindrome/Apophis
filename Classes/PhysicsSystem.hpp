/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PhysicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"
#include "CollisionManager.hpp"

#include <entityx/entityx.h>

#include <Box2D/Dynamics/b2World.h>


class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
public:
    explicit PhysicsSystem(entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const CreateBody& event);
	virtual void receive(const SetPosition& event);
	virtual void receive(const SetRotation& event);
	virtual void receive(const SetVelocity& event);
	virtual void receive(const ApplyForce& event);
	virtual void receive(const ApplyLinearImpulse& event);
	virtual void receive(const ApplyAngularImpulse& event);

private:
	b2World world;
	CollisionManager collisionManager;
};