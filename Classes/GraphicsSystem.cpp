/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "Renderables.hpp"
#include "TagsComponent.hpp"
#include "GraphicsSystem.hpp"
#include "TransformComponent.hpp"

#include <cocos/base/CCEventDispatcher.h>

#include <brigand/algorithms/for_each.hpp>


GraphicsSystem::GraphicsSystem(cocos2d::Node* gameNode) :
	gameNode(gameNode)
{
}

void GraphicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<EntityParsed>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<SpriteComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<LabelComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<ParticleComponent>>(*this);
}

void GraphicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	brigand::for_each<Renderables>([&entityManager](auto renderableElement)
	{
		entityManager.each<decltype(renderableElement)::type, TransformComponent>([](auto entity, auto& renderable, auto& transform)
		{
			renderable.setPosition({ transform.getPosition().x * Constants::PTM_RATIO, transform.getPosition().y * Constants::PTM_RATIO });
			renderable.setRotation(-transform.getAngle());
		});
	});

	updateHealthBar();
}

void GraphicsSystem::receive(const EntityParsed& event)
{
	if (auto[tags, health] = event.entity.components<TagsComponent, HealthComponent>(); tags && health && tags->hasTag("Player"))
	{
		playerHealth = health;
	}

	brigand::for_each<Renderables>([event](auto renderableElement)
	{
		if (auto[renderable, transform] = event.entity.components<decltype(renderableElement)::type, TransformComponent>(); renderable && transform)
		{
			renderable->setPosition({ transform->getPosition().x * Constants::PTM_RATIO, transform->getPosition().y * Constants::PTM_RATIO });
			renderable->setRotation(-transform->getAngle());
		}
	});
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<SpriteComponent>& event)
{
	gameNode->addChild(event.component->getNode());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<LabelComponent>& event)
{
	gameNode->addChild(event.component->getNode());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<ParticleComponent>& event)
{
	gameNode->addChild(event.component->getNode());
}

void GraphicsSystem::updateHealthBar()
{
	if (playerHealth)
	{
		auto healthPercent = playerHealth->getCurrentHitpoints() / playerHealth->getMaxHitpoints() * 100.f;

		gameNode->getEventDispatcher()->dispatchCustomEvent("setHealthBar", &healthPercent);
	}
}