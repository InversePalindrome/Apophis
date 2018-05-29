/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "StrikerSystem.hpp"


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
			   eventManager->emit(Seek{ context.striker, playerBody->getPosition() });
			   eventManager->emit(Face{ context.striker, playerBody->getPosition() });
	          eventManager->emit(ShootProjectile{ context.striker, playerBody->getPosition() });

		       return beehive::Status::SUCCESS;
	       }

	     return beehive::Status::FAILURE;
      })
      .void_leaf([this](auto& context)
      {
	      eventManager->emit(Flee{ context.striker, playerBody->getPosition() });
		  eventManager->emit(Face{ context.striker, -playerBody->getPosition() });
      }).end().end()
     .void_leaf([this](auto& context)
      {
	     eventManager->emit(Wander{ context.striker });
		 eventManager->emit(Face{ context.striker, context.body->getPosition() + context.body->getLinearVelocity() });
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
	entityx::ComponentHandle<VisionComponent> vision;
	entityx::ComponentHandle<HealthComponent> health;

	for (auto entity : entityManager.entities_with_components(striker, body, vision, health))
	{
		strikerTree.process(StrikerContext{ entity, body, vision, health });
	}
}

void StrikerSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		playerBody = event.entity.component<BodyComponent>();
	}
}