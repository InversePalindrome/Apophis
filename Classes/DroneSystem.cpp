/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.cpp
InversePalindrome.com
*/


#include "DroneSystem.hpp"
#include "TagsComponent.hpp"
#include "SteeringBehaviors.hpp"
#include "TransformComponent.hpp"


DroneSystem::DroneSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	droneTree(beehive::Builder<DroneContext>()
	.selector()
	.sequence()
	.leaf([&entityManager](auto& context)
    {
	   if (auto leaderEntity = entityManager.get(entityManager.create_id(context.follow.getLeaderID())))
	   {
		   if (const auto leaderTransform = leaderEntity.component<TransformComponent>(); leaderTransform && 
			   (leaderTransform->getPosition() - context.body.getPosition()).Length() <= context.vision.getVisionDistance())
		   {
			   return true;
		   }
	   }

	   return false;   
    }
	).void_leaf([&entityManager](auto& context) 
	{
		auto leaderEntity = entityManager.get(entityManager.create_id(context.follow.getLeaderID()));

		if (const auto leaderBody = leaderEntity.component<BodyComponent>())
		{
			auto directionVector = leaderBody->getLinearVelocity();
			directionVector.Normalize();
			directionVector *= context.follow.getDistanceFromLeader();

			const auto aheadPoint = leaderBody->getPosition() + directionVector;
			const auto behindPoint = leaderBody->getPosition() - directionVector;

			if (b2RayCastOutput rayOutput; context.body.raycast(rayOutput, { leaderBody->getPosition(), aheadPoint, 1.f }))
			{
				context.body.applyLinearImpulse(SteeringBehaviors::evade(context.body.getPosition(), leaderBody->getPosition(), context.body.getLinearVelocity(), leaderBody->getLinearVelocity(), context.speed.getMaxLinearSpeed()));
			}

			context.body.applyLinearImpulse(SteeringBehaviors::arrive(context.body.getPosition(), behindPoint, context.body.getLinearVelocity(), context.arrive.getSlowRadius(), context.speed.getMaxLinearSpeed()));
			context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.body.getPosition() + context.body.getLinearVelocity(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
		}

		std::vector<b2Vec2> neighborPositions;

		entityManager.each<FlockComponent, BodyComponent>([&context, &neighborPositions](auto entity, const auto& flock, const auto& body) 
		{
			if (context.entity != entity && context.flock.getGroupID() == flock.getGroupID() && (context.body.getPosition() - body.getPosition()).Length() <= context.flock.getGroupRadius())
			{
				neighborPositions.push_back(body.getPosition());
			}
		});
		
		context.body.applyLinearImpulse(SteeringBehaviors::separateForce(context.body.getPosition(), neighborPositions, context.flock.getSeparationForce()));
	})
	.end()
	.void_leaf([](auto& context)
	{
		context.body.applyLinearImpulse(SteeringBehaviors::wander(context.body.getPosition(), context.body.getLinearVelocity(), context.wander.getWanderDistance(), context.wander.getWanderRadius(), context.wander.getWanderRate(), context.wander.getWanderAngle(), context.speed.getMaxLinearSpeed()));
		context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.body.getPosition() + context.body.getLinearVelocity(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
	}).end().build())
{
}

void DroneSystem::configure(entityx::EventManager& eventManager)
{
}

void DroneSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityManager.each<TagsComponent, BodyComponent, WanderComponent, SpeedComponent, ArriveComponent, FollowComponent, FlockComponent, VisionComponent>
	([this](auto entity, const auto& tags, auto& body, auto& wander, const auto& speed, const auto& arrive, const auto& follow, const auto& flock, const auto& vision)
	{
		if (tags.hasTag("Drone"))
		{
			droneTree.process(DroneContext{ entity, body, wander, speed, arrive, follow, flock, vision});
		}
	});
}