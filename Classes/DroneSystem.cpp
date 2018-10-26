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
			auto leaderBehindPoint = leaderBody->getLinearVelocity();
			leaderBehindPoint *= -1.f;
			leaderBehindPoint.Normalize();
			leaderBehindPoint *= context.follow.getDistanceFromLeader();

			context.body.applyLinearImpulse(SteeringBehaviors::arrive(context.body.getPosition(), leaderBehindPoint, context.body.getLinearVelocity(), context.arrive.getSlowRadius(), context.speed.getMaxLinearSpeed()));
			context.body.applyAngularImpulse(SteeringBehaviors::face(leaderBody->getAngle(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
		}
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
	entityManager.each<TagsComponent, BodyComponent, WanderComponent, SpeedComponent, ArriveComponent, FollowComponent, FlockComponent, VisionComponent>([this](auto entity, const auto& tags, auto& body, auto& wander, const auto& speed, const auto& arrive, const auto& follow, const auto& flock, const auto& vision)
	{
		if (tags.hasTag("Drone"))
		{
			droneTree.process(DroneContext{ entity, body, wander, speed, arrive, follow, flock, vision});
		}
	});
}