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
#include "PathwayComponent.hpp"
#include "DestructionListener.hpp"
#include "DistanceJointComponent.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <entityx/System.h> 

#include <list>


class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<PhysicsSystem>
{
public:
    PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager);

    virtual void configure(entityx::EventManager& eventManager) override;
    virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
    virtual void receive(const entityx::EntityDestroyedEvent& event);
    virtual void receive(const entityx::ComponentAddedEvent<BodyComponent>& event);
    virtual void receive(const entityx::ComponentRemovedEvent<BodyComponent>& event);
    virtual void receive(const UpdateTransform& event);
    virtual void receive(const ComponentLoaded<DistanceJointComponent>& event);
    virtual void receive(const ComponentLoaded<PathwayComponent>& event);

private:
    b2World world;
    CollisionManager collisionManager;
    CollisionFilter collisionFilter;
    DestructionListener destructionListener;

    entityx::EntityManager& entityManager;

    std::list<entityx::Entity> bodiesUserData;

    void destroyBody(b2Body* body);
    void destroyJoint(b2Joint* joint);
};