/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "StrikerSystem.hpp"
#include "SteeringBehaviors.hpp"


StrikerSystem::StrikerSystem()  :
	strikerTree(beehive::Builder<StrikerContext>()
	.selector()
	.sequence()
	.leaf([this](auto& context)
    {
	     return (playerTransform->getPosition() - context.body->getPosition()).Length() <= context.vision->getVisionDistance();
    })
	.selector()
	.sequence()
	.leaf([](auto& context)
	{
		const auto healthBreakPercent = 0.2f;

		return context.health->getCurrentHitpoints() >= context.health->getMaxHitpoints() * healthBreakPercent;
	})
	.void_leaf([this](auto& context)
	{
		context.body->applyLinearImpulse(SteeringBehaviors::seek(context.body->getPosition(), playerTransform->getPosition(), context.body->getLinearVelocity(), context.speed->getMaxLinearSpeed()));
		context.body->applyAngularImpulse(SteeringBehaviors::face(context.body->getPosition(), playerTransform->getPosition(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));

		eventManager->emit(ShootProjectile{ context.striker });
	})
	.end()
	.void_leaf([this](auto& context)
	{
		context.body->applyLinearImpulse(SteeringBehaviors::seek(context.body->getPosition(), playerTransform->getPosition(), context.body->getLinearVelocity(), -context.speed->getMaxLinearSpeed()));
		context.body->applyAngularImpulse(SteeringBehaviors::face(playerTransform->getPosition(), context.body->getPosition(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));
	}).end().end()
	.void_leaf([](auto& context)
	{
		context.body->applyLinearImpulse(SteeringBehaviors::wander(context.body->getPosition(), context.body->getLinearVelocity(), context.wander->getWanderDistance(), context.wander->getWanderRadius(), context.wander->getWanderRate(), context.wander->getWanderAngle(), context.speed->getMaxLinearSpeed()));
		context.body->applyAngularImpulse(SteeringBehaviors::face(context.body->getPosition(), context.body->getPosition() + context.body->getLinearVelocity(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));
	}).end().build())
{
}
	  
void StrikerSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityCreated>(*this);
}

void StrikerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	if (playerTransform)
	{
		entityx::ComponentHandle<Striker> striker;
		entityx::ComponentHandle<BodyComponent> body;
		entityx::ComponentHandle<SpeedComponent> speed;
		entityx::ComponentHandle<WanderComponent> wander;
		entityx::ComponentHandle<VisionComponent> vision;
		entityx::ComponentHandle<HealthComponent> health;

		for (auto entity : entityManager.entities_with_components(striker, body, speed, wander, vision, health))
		{
			strikerTree.process(StrikerContext{ entity, body, speed, wander, vision, health });
		}
	}
}

void StrikerSystem::receive(const EntityCreated& event)
{
	if (event.entity.has_component<Player>())
	{
		playerTransform = event.entity.component<TransformComponent>();
	}
}