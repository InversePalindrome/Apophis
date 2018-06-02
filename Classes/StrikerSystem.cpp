/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "StrikerSystem.hpp"
#include "SteeringBehaviors.hpp"


StrikerSystem::StrikerSystem() :
	strikerTree(beehive::Builder<StrikerContext>()
		.selector()
		.sequence()
		.leaf([this](auto& context)
        {
	       if (playerBody.valid() && (playerBody->getPosition() - context.body->getPosition()).Length() <= context.vision->getVisionDistance())
	         {
		        return beehive::Status::SUCCESS;
	         }

        	return beehive::Status::FAILURE;
       })
       .selector()
       .leaf([this](auto& context)
       {
		   if (context.health->getCurrentHitpoints() >= context.health->getMaxHitpoints() * 0.2)
		   {
	           context.body->applyLinearImpulse(SteeringBehaviors::seek(context.body->getPosition(), playerBody->getPosition(), context.body->getLinearVelocity(), context.speed->getMaxLinearSpeed()));
			   context.body->applyAngularImpulse(SteeringBehaviors::face(context.body->getPosition(), playerBody->getPosition(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));
			   
			   //eventManager->emit(ShootProjectile{ context.striker, playerBody->getPosition() });
			
		       return beehive::Status::SUCCESS;
	       }

	     return beehive::Status::FAILURE;
      })
      .void_leaf([this](auto& context)
      {
		  context.body->applyLinearImpulse(SteeringBehaviors::seek(context.body->getPosition(), -playerBody->getPosition(), context.body->getLinearVelocity(), context.speed->getMaxLinearSpeed()));
	      context.body->applyAngularImpulse(SteeringBehaviors::face(context.body->getPosition(), -playerBody->getPosition(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));
      }).end().end()
     .void_leaf([this](auto& context)
      {
		  context.body->applyLinearImpulse(SteeringBehaviors::wander(context.body->getPosition(), context.body->getLinearVelocity(), context.wander->getWanderDistance(), context.wander->getWanderRadius(), context.wander->getWanderRate(), context.wander->getWanderAngle(), context.speed->getMaxLinearSpeed()));
		  context.body->applyAngularImpulse(SteeringBehaviors::face(context.body->getPosition(), context.body->getPosition() + context.body->getLinearVelocity(), context.body->getAngle(), context.body->getAngularVelocity(), context.body->getInertia()));
      })
      .end().build())
{
}
	  
void StrikerSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<EntityParsed>(*this);
}

void StrikerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
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

void StrikerSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		playerBody = event.entity.component<BodyComponent>();
	}
}