/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "PhysicsSystem.hpp"
#include "ForceComponent.hpp"
#include "ImpulseComponent.hpp"
#include "AnchorPointComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <boost/math/constants/constants.hpp>

#include <sstream>
#include <variant>


PhysicsSystem::PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager),
	entityManager(entityManager)
{
	world.SetContactListener(&collisionManager);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
	eventManager.subscribe<RayCast>(*this);
	eventManager.subscribe<QueryAABB>(*this);
	eventManager.subscribe<SetBodyPosition>(*this);
	eventManager.subscribe<SetBodyAngle>(*this);
	eventManager.subscribe<SetLinearVelocity>(*this);
	eventManager.subscribe<SetAngularVelocity>(*this);
	eventManager.subscribe<ApplyLinearImpulse>(*this);
	eventManager.subscribe<ApplyAngularImpulse>(*this);
	eventManager.subscribe<ApplyLinearForce>(*this);
	eventManager.subscribe<ApplyRotationalForce>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;

	for (auto entity : entityManager.entities_with_components(body, speed))
	{
		limitLinearSpeed(body, speed);
		limitAngularSpeed(body, speed);
	}

	updateWorld();
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto body = entity.component<BodyComponent>())
	{
		delete static_cast<entityx::Entity*>(body->getUserData());

		world.DestroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	delete static_cast<entityx::Entity*>(event.component->getUserData());

    world.DestroyBody(event.component->getBody());
}

void PhysicsSystem::receive(const CreateBody& event)
{
	event.entity.assign<BodyComponent>(event.bodyNode, world)->setUserData(new entityx::Entity(event.entity));
}

void PhysicsSystem::receive(const CreateDistanceJoint& event)
{
	auto bodyA = event.entityA.component<BodyComponent>();
	auto bodyB = event.entityB.component<BodyComponent>();
	auto anchorA = event.entityA.component<AnchorPointComponent>();
	auto anchorB = event.entityB.component<AnchorPointComponent>();

	if (bodyA && bodyB && anchorA && anchorB)
	{
		entityManager.create().assign<DistanceJointComponent>(world, bodyA->getBody(), bodyB->getBody(), anchorA->getAnchorPoint(), anchorB->getAnchorPoint());
	}
}

void PhysicsSystem::receive(const RayCast& event)
{
	world.RayCast(&event.rayCastQuery, event.p1, event.p2);
}

void PhysicsSystem::receive(const QueryAABB& event)
{
	world.QueryAABB(&event.areaQuery, event.aabb);
}

void PhysicsSystem::receive(const SetBodyPosition& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setPosition(event.position);
	}
}

void PhysicsSystem::receive(const SetBodyAngle& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setAngle(event.angle);
	}
}

void PhysicsSystem::receive(const SetLinearVelocity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setLinearVelocity(event.velocity);
	}
}

void PhysicsSystem::receive(const SetAngularVelocity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setAngularVelocity(event.velocity);
	}
}

void PhysicsSystem::receive(const ApplyLinearImpulse& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (body && impulse)
	{
		body->applyLinearImpulse(impulse->getLinearImpulse() * event.direction);
	}
}

void PhysicsSystem::receive(const ApplyAngularImpulse& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (body && impulse)
	{
		body->applyAngularImpulse(impulse->getAngularImpulse() * event.direction);
	}
}

void PhysicsSystem::receive(const ApplyLinearForce& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();

	if (body && force)
	{
		body->applyLinearForce(force->getLinearForce() * event.direction);
	}
}

void PhysicsSystem::receive(const ApplyRotationalForce& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();

	if (body && force)
	{
		body->applyRotationalForce(force->getRotationalForce() * event.direction);
	}
}

void PhysicsSystem::updateWorld()
{
	const float timeStep = 1.f / 60.f;
	const int velocityIterations = 6;
	const int positionIterations = 2;

	world.Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsSystem::limitLinearSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed)
{
	if (body->getLinearVelocity().Length() > speed->getMaxLinearSpeed())
	{
		body->setLinearVelocity(speed->getMaxLinearSpeed() / body->getLinearVelocity().Length() * body->getLinearVelocity());
	}
}

void PhysicsSystem::limitAngularSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed)
{
	if (std::fabs(body->getAngularVelocity()) > speed->getMaxAngularSpeed())
	{
		body->setAngularVelocity(speed->getMaxAngularSpeed() / body->getAngularVelocity());
	}
}