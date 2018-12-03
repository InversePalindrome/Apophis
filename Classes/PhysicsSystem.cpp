/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Joints.hpp"
#include "Constants.hpp"
#include "Conversions.hpp"
#include "PhysicsSystem.hpp"
#include "TransformComponent.hpp"

#include <brigand/algorithms/for_each.hpp>


PhysicsSystem::PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager),
	destructionListener(entityManager),
	entityManager(entityManager)
{
	world.SetContactListener(&collisionManager);
	world.SetContactFilter(&collisionFilter);
	world.SetDestructionListener(&destructionListener);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<BodyComponent>>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<UpdateTransform>(*this);
	eventManager.subscribe<ComponentLoaded<DistanceJointComponent>>(*this);
	eventManager.subscribe<ComponentLoaded<PathwayComponent>>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityManager.each<TransformComponent, BodyComponent>([](auto entity, auto& transform, const auto& body)
	{
		transform.setPosition(body.getPosition());
		transform.setAngle(Conversions::radiansToDegrees(body.getAngle()));
	});

	world.Step(Constants::TIMESTEP, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);

	collisionManager.update();
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;
	
	brigand::for_each<Joints>([this, entity](auto jointElement) mutable
	{
		if (auto joint = entity.component<decltype(jointElement)::type>())
		{
			destroyJoint(joint->getJoint());
		}
	});

	if (auto body = entity.component<BodyComponent>())
	{
		destroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentAddedEvent<BodyComponent>& event)
{
	bodiesUserData.push_back(event.entity);

	auto body = event.component;

	body->setBody(world.CreateBody(&b2BodyDef())); 
	body->setUserData(&bodiesUserData.back());
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	bodiesUserData.erase(std::remove(std::begin(bodiesUserData), std::end(bodiesUserData), event.entity));

	auto body = event.component;

	body->setUserData(nullptr);
	destroyBody(body->getBody());
}

void PhysicsSystem::receive(const UpdateTransform& event)
{
	if (auto[body, transform] = event.entity.components<BodyComponent, TransformComponent>(); body && transform)
	{
		body->setPosition(transform->getPosition());
		body->setAngle(Conversions::degreesToRadians(transform->getAngle()));
	}
}

void PhysicsSystem::receive(const ComponentLoaded<DistanceJointComponent>& event)
{
	auto joint = event.component;

	if (auto entityA = entityManager.get(entityManager.create_id(joint->getEntityIDA())),
		entityB = entityManager.get(entityManager.create_id(joint->getEntityIDB()));
	    entityA && entityB)
	{
		if (auto bodyA = entityA.component<BodyComponent>(),
			bodyB = entityB.component<BodyComponent>();
		    bodyA && bodyB)
		{ 
			b2DistanceJointDef distanceJointDef;
			distanceJointDef.Initialize(bodyA->getBody(), bodyB->getBody(), joint->getLocalAnchorA(), joint->getLocalAnchorB());
			joint->setDistanceJoint(static_cast<b2DistanceJoint*>(world.CreateJoint(&distanceJointDef)));
			joint->setJoint(joint->getDistanceJoint());
		}
	}
}

void PhysicsSystem::receive(const ComponentLoaded<PathwayComponent>& event)
{
	bodiesUserData.push_back(event.entity);

	b2BodyDef pathwayBodyDef;
	pathwayBodyDef.userData = &bodiesUserData.back();

	auto* body = world.CreateBody(&pathwayBodyDef);

	for (const auto& pathwayPoint : *event.component.get())
	{
		b2CircleShape circle;
		circle.m_p = pathwayPoint;
		circle.m_radius = 0.1f;

		b2FixtureDef fixtureDef;
		
		fixtureDef.isSensor = true;
		fixtureDef.shape = &circle;

		body->CreateFixture(&fixtureDef);
	}
}

void PhysicsSystem::destroyBody(b2Body* body)
{
    world.DestroyBody(body); 
}

void PhysicsSystem::destroyJoint(b2Joint* joint)
{
	world.DestroyJoint(joint); 
}