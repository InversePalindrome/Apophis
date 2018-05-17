/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "AreaQuery.hpp"
#include "SteerComponent.hpp"
#include "FlockComponent.hpp"
#include "SteeringSystem.hpp"
#include "AvoidComponent.hpp"
#include "QueueComponent.hpp"
#include "PhysicsUtility.hpp"
#include "ArriveComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "ImpulseComponent.hpp"
#include "PredictComponent.hpp"
#include "SteeringBehaviors.hpp"


void SteeringSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<EntityCreated>(*this);
	eventManager.subscribe<Seek>(*this);
	eventManager.subscribe<Flee>(*this);
	eventManager.subscribe<Pursue>(*this);
	eventManager.subscribe<Evade>(*this);
	eventManager.subscribe<Arrive>(*this);
	eventManager.subscribe<Follow>(*this);
	eventManager.subscribe<Wander>(*this);
	eventManager.subscribe<Patrol>(*this);
	eventManager.subscribe<Avoid>(*this);
	eventManager.subscribe<Align>(*this);
	eventManager.subscribe<Cohesion>(*this);
	eventManager.subscribe<Separate>(*this);
	eventManager.subscribe<Queue>(*this);
}

void SteeringSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{ 
	entityx::ComponentHandle<SteerComponent> steer;
	entityx::ComponentHandle<BodyComponent> body;

	for (auto entity : entityManager.entities_with_components(steer, body))
	{
		body->applyLinearImpulse(steer->getSteeringForce());

		eventManager.emit(RotateEntity{ entity, body->getLinearVelocity() });

		steer->setSteeringForce({ 0.f, 0.f });
	}
}

void SteeringSystem::receive(const EntityCreated& event)
{
	if (event.entity.has_component<Player>())
	{
		if (auto playerBody = event.entity.component<BodyComponent>())
		{
			this->playerBody = playerBody;
		}
		if (auto playerVision = event.entity.component<VisionComponent>())
		{
			this->playerVision = playerVision;
		}
	}
}

void SteeringSystem::receive(const Seek& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (steer && body && impulse && playerBody.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::seek(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), impulse->getImpulse()));
	}
}

void SteeringSystem::receive(const Flee& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();

	if (steer && body && impulse && playerBody.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::seek(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), -impulse->getImpulse()));
	}
}

void SteeringSystem::receive(const Pursue& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (steer && body && impulse && pursue && playerBody.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::pursue(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), impulse->getImpulse(), pursue->getPredictionTime()));
	}
}

void SteeringSystem::receive(const Evade& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto evade = event.entity.component<EvadeComponent>();

	if (steer && body && impulse && evade && playerBody.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::pursue(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), -impulse->getImpulse(), evade->getPredictionTime()));
	}
}

void SteeringSystem::receive(const Arrive& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto arrive = event.entity.component<ArriveComponent>();

	if (steer && body && impulse && arrive && playerBody.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::arrive(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), impulse->getImpulse(), arrive->getSlowingRadius()));
	}
}

void SteeringSystem::receive(const Follow& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto follow = event.entity.component<FollowComponent>();

	if (steer && body && impulse && follow && playerBody.valid() && playerVision.valid())
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::follow(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), playerVision->getVisionDistance(), follow->getDistanceFromLeader(), impulse->getImpulse()));
	}
}

void SteeringSystem::receive(const Wander& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto wander = event.entity.component<WanderComponent>();
	
	if (steer && body && impulse && wander)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::wander(body->getPosition(), body->getLinearVelocity(), wander->getWanderDistance(), wander->getWanderRadius(), wander->getWanderRate(), wander->getWanderAngle(), impulse->getImpulse()));
	}
}

void SteeringSystem::receive(const Patrol& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto patrol = event.entity.component<PatrolComponent>();

	if (steer && body && impulse && patrol)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::seek(body->getPosition(), patrol->getCurrentPoint(), body->getLinearVelocity(), impulse->getImpulse()));

		if (body->contains(patrol->getCurrentPoint()))
		{
			patrol->nextPoint();
		}
	}
}

void SteeringSystem::receive(const Avoid& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto avoid = event.entity.component<AvoidComponent>();

	if (steer && body && avoid)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::avoid(body->getBody(), avoid->getAvoidanceDistance(), avoid->getAvoidanceForce()));
	}
}

void SteeringSystem::receive(const Align& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto flock = event.entity.component<FlockComponent>();

	if (steer && body && impulse && flock)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::align(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType));
	}
}

void SteeringSystem::receive(const Cohesion& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto flock = event.entity.component<FlockComponent>();

	if (steer && body && impulse && flock)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::cohesion(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType));
	}
}

void SteeringSystem::receive(const Separate& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto flock = event.entity.component<FlockComponent>();

	if (steer && body && impulse && flock)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::separate(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType));
	}
}

void SteeringSystem::receive(const Queue& event)
{
	auto steer = event.entity.component<SteerComponent>();
	auto body = event.entity.component<BodyComponent>();
	auto impulse = event.entity.component<ImpulseComponent>();
	auto flock = event.entity.component<FlockComponent>();
	auto queue = event.entity.component<QueueComponent>();

	if (steer && body && impulse && flock && queue)
	{
		steer->setSteeringForce(steer->getSteeringForce() + SteeringBehaviors::queue(body->getBody(), steer->getSteeringForce(), flock->getGroupRadius(), queue->getQueueDistance(), queue->getShrinkingFactor(), queue->getSteeringBrakeFactor(), impulse->getImpulse(), body->getBodyData().objectType));
	}
}