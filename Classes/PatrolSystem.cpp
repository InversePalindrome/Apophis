/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolSystem.cpp
InversePalindrome.com
*/


#include "PatrolSystem.hpp"
#include "ObjectComponent.hpp"
#include "SteeringBehaviors.hpp"


PatrolSystem::PatrolSystem() :
	patrolTree(beehive::Builder<PatrolContext>()
	.void_leaf([](auto& context)
   {
	   context.body.applyLinearImpulse(SteeringBehaviors::seek(context.body.getPosition(), context.patrol.getCurrentPatrolPoint(), context.body.getLinearVelocity(), context.speed.getMaxLinearSpeed()));
   }).build())
{
}

void PatrolSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityManager.each<ObjectComponent, BodyComponent, SpeedComponent, PatrolComponent>
		([this](auto entity, const auto& object, auto& body, const auto& speed, auto& patrol)
	{
		if (object.getObjectType() == +ObjectType::Patrol)
		{
			patrolTree.process(PatrolContext{ entity, body, speed, patrol });
		}
	});
}