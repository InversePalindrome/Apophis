/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteeringSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "AreaQuery.hpp"
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
}

void SteeringSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{ 
	entityx::ComponentHandle<AI> ai;
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<ImpulseComponent> impulse;

	for (auto entity : entityManager.entities_with_components(ai, body, impulse))
	{
		b2Vec2 steeringForce(0.f, 0.f);

		if (playerBody.valid())
		{
			if (entity.has_component<SeekComponent>())
			{
				steeringForce += SteeringBehaviors::seek(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), impulse->getImpulse());
			}
			if (entity.has_component<FleeComponent>())
			{
				steeringForce += SteeringBehaviors::seek(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), -impulse->getImpulse());
			}
			if (auto pursue = entity.component<PursueComponent>())
			{
				steeringForce += SteeringBehaviors::pursue(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), impulse->getImpulse(), pursue->getPredictionTime());
			}
			if (auto evade = entity.component<EvadeComponent>())
			{
				steeringForce += SteeringBehaviors::pursue(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), -impulse->getImpulse(), evade->getPredictionTime());
			}
			if (auto arrive = entity.component<ArriveComponent>())
			{
				steeringForce += SteeringBehaviors::arrive(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), impulse->getImpulse(), arrive->getSlowingRadius());
			}
			if (auto follow = entity.component<FollowComponent>())
			{
				steeringForce += SteeringBehaviors::follow(body->getPosition(), playerBody->getPosition(), body->getLinearVelocity(), playerBody->getLinearVelocity(), follow->getLeaderSight(), follow->getDistanceFromLeader(), impulse->getImpulse());
			}
		}

		if (auto wander = entity.component<WanderComponent>())
		{
			steeringForce += SteeringBehaviors::wander(body->getPosition(), body->getLinearVelocity(), wander->getWanderDistance(), wander->getWanderRadius(), wander->getWanderRate(), wander->getWanderAngle(), impulse->getImpulse());
		}

		if (auto patrol = entity.component<PatrolComponent>())
		{
			steeringForce += SteeringBehaviors::seek(body->getPosition(), patrol->getCurrentPoint(), body->getLinearVelocity(), impulse->getImpulse());

			if (body->contains(patrol->getCurrentPoint()))
			{
				patrol->nextPoint();
			}
		}

		if (auto avoid = entity.component<AvoidComponent>())
		{
			steeringForce += SteeringBehaviors::avoid(body->getBody(), avoid->getAvoidanceDistance(), avoid->getAvoidanceForce());
		}

		if (auto flock = entity.component<FlockComponent>())
		{
			if (entity.has_component<AlignComponent>())
			{
				steeringForce += SteeringBehaviors::align(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType);
			}
			if (entity.has_component<CohesionComponent>())
			{
				steeringForce += SteeringBehaviors::cohesion(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType);
			}
			if (entity.has_component<SeparateComponent>())
			{
				steeringForce += SteeringBehaviors::separate(body->getBody(), flock->getGroupRadius(), impulse->getImpulse(), body->getBodyData().objectType);
			}
			if (auto queue = entity.component<QueueComponent>())
			{
				steeringForce += SteeringBehaviors::queue(body->getBody(), steeringForce, flock->getGroupRadius(), queue->getQueueDistance(), queue->getShrinkingFactor(), queue->getSteeringBrakeFactor(), impulse->getImpulse(), body->getBodyData().objectType);
			}
		}
		
	    body->applyLinearImpulse(steeringForce);

		if (entity.has_component<FaceComponent>())
		{
			eventManager.emit(RotateEntity{ entity, body->getLinearVelocity() });
		}
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
	}
}