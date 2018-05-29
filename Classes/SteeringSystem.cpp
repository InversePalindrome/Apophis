/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringSystem.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"
#include "FlockComponent.hpp"
#include "SteeringSystem.hpp"
#include "AvoidComponent.hpp"
#include "QueueComponent.hpp"
#include "PursueComponent.hpp"
#include "ArriveComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "ImpulseComponent.hpp"
#include "SteeringBehaviors.hpp"


void SteeringSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<Seek>(*this);
	eventManager.subscribe<Flee>(*this);
	eventManager.subscribe<Pursue>(*this);
	eventManager.subscribe<Evade>(*this);
	eventManager.subscribe<Arrive>(*this);
	eventManager.subscribe<Follow>(*this);
	eventManager.subscribe<Wander>(*this);
	eventManager.subscribe<Avoid>(*this);
	eventManager.subscribe<Orbit>(*this);
	eventManager.subscribe<Align>(*this);
	eventManager.subscribe<Cohesion>(*this);
	eventManager.subscribe<Separate>(*this);
	eventManager.subscribe<Queue>(*this);
	eventManager.subscribe<Face>(*this);
}

void SteeringSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{ 
	
}

void SteeringSystem::receive(const Seek& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (body && impulse)
	{
		body->applyLinearImpulse(SteeringBehaviors::seekForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Flee& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (body && impulse)
	{
		body->applyLinearForce(SteeringBehaviors::seekForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), -impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Pursue& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (body && impulse && pursue)
	{
		body->applyLinearForce(SteeringBehaviors::pursueForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), event.targetVelocity, pursue->getPredictionTime(), impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Evade& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (body && impulse && pursue)
	{
		body->applyLinearForce(SteeringBehaviors::pursueForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), event.targetVelocity, pursue->getPredictionTime(), -impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Arrive& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto arrive = event.entity.component<ArriveComponent>();

	if (body && impulse && arrive)
	{
		body->applyLinearForce(SteeringBehaviors::arriveForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), arrive->getSlowRadius(), impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Follow& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto follow = event.entity.component<FollowComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (body && impulse && follow && pursue)
	{
		body->applyLinearImpulse(SteeringBehaviors::followForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), event.targetVelocity, event.targetVision, follow->getDistanceFromLeader(), pursue->getPredictionTime(), impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Wander& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto wander = event.entity.component<WanderComponent>();

	if (body && impulse && wander)
	{
		body->applyLinearImpulse(SteeringBehaviors::wanderForce(body->getPosition(), body->getLinearVelocity(), wander->getWanderDistance(), wander->getWanderRadius(), wander->getWanderRate(), wander->getWanderAngle(), impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Avoid& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto avoid = event.entity.component<AvoidComponent>();

	if (body && avoid)
	{
		body->applyLinearImpulse(SteeringBehaviors::avoidForce(body->getWorld(), body->getPosition(), body->getLinearVelocity(), avoid->getAvoidanceDistance(), avoid->getAvoidanceForce()));
	}
}

void SteeringSystem::receive(const Orbit& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (body && impulse)
	{
		body->applyLinearImpulse(SteeringBehaviors::orbitForce(body->getPosition(), event.primaryPosition, impulse->getLinearImpulse()));
	}
}

void SteeringSystem::receive(const Align& event)
{
	
}

void SteeringSystem::receive(const Cohesion& event)
{
	
}

void SteeringSystem::receive(const Separate& event)
{

}

void SteeringSystem::receive(const Queue& event)
{
	
}

void SteeringSystem::receive(const Face& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->applyAngularImpulse(SteeringBehaviors::faceForce(body->getPosition(), event.targetPosition, body->getAngle(), body->getAngularVelocity(), body->getInertia()));
	}
}