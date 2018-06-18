/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Constants.hpp"
#include "Renderables.hpp"
#include "GraphicsSystem.hpp"
#include "AnimationComponent.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCActionInterval.h>
#include <cocos/base/CCEventDispatcher.h>

#include <brigand/algorithms/for_each.hpp>


GraphicsSystem::GraphicsSystem(cocos2d::Node* gameNode, Map& map) :
	gameNode(gameNode),
	map(map)
{
}

void GraphicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<SpriteComponent>>(*this); 
	eventManager.subscribe<entityx::ComponentAddedEvent<ParticleComponent>>(*this);
	eventManager.subscribe<EntityParsed>(*this);
	eventManager.subscribe<PlayAnimation>(*this);
	eventManager.subscribe<StopAnimation>(*this);
}

void GraphicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	brigand::for_each<Renderables>([&entityManager](auto renderableElement)
	{
		using RenderableComponent = decltype(renderableElement)::type;

		entityx::ComponentHandle<RenderableComponent> renderable;
		entityx::ComponentHandle<GeometryComponent> geometry;

		for (auto entity : entityManager.entities_with_components(renderable, geometry))
		{
			renderable->setPosition({ geometry->getPosition().x * Constants::PTM_RATIO, geometry->getPosition().y * Constants::PTM_RATIO });
			renderable->setRotation(geometry->getAngle());
		}
	});
	
	updateView();
	updateHealthBar();
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<SpriteComponent>& event)
{
	gameNode->addChild(event.component->getSprite());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<ParticleComponent>& event)
{
	gameNode->addChild(event.component->getParticleSystem());
}

void GraphicsSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		playerGeometry = event.entity.component<GeometryComponent>();
		playerHealth = event.entity.component<HealthComponent>();
	}
}

void GraphicsSystem::receive(const PlayAnimation& event)
{
	auto sprite = event.entity.component<SpriteComponent>();
	auto animation = event.entity.component<AnimationComponent>();

	if (sprite && animation && animation->hasAnimation(event.animation))
	{
		auto* animate = cocos2d::Animate::create(animation->getAnimation(event.animation));

		if (event.loop)
		{
			animation->addAction(event.animation, sprite->getSprite()->runAction(cocos2d::RepeatForever::create(animate)));
		}
		else
		{
			animation->addAction(event.animation, sprite->getSprite()->runAction(animate));
		}
	}
}

void GraphicsSystem::receive(const StopAnimation& event)
{
	auto sprite = event.entity.component<SpriteComponent>();
	auto animation = event.entity.component<AnimationComponent>();

	if (sprite && animation && animation->hasAction(event.animation))
	{
		sprite->getSprite()->stopAction(animation->getAction(event.animation));
		animation->removeAction(event.animation);
	}
}

void GraphicsSystem::updateView()
{
	if (playerGeometry)
	{
		const auto playerNodePosition = cocos2d::Vec2(playerGeometry->getPosition().x * Constants::PTM_RATIO, playerGeometry->getPosition().y * Constants::PTM_RATIO);
		const auto worldPoint = gameNode->convertToWorldSpace(playerNodePosition);
		const auto windowSize = cocos2d::Director::getInstance()->getWinSize();

		if (std::abs(playerNodePosition.x) < map.getDimensions().x * Constants::PTM_RATIO / 2.f - windowSize.width / 2.f)
		{
			gameNode->setPositionX(gameNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
		}
		if (std::abs(playerNodePosition.y) < map.getDimensions().y * Constants::PTM_RATIO / 2.f - windowSize.height / 2.f)
		{
			gameNode->setPositionY(gameNode->getPosition().y - worldPoint.y + windowSize.height / 2.f);
		}
	}
}

void GraphicsSystem::updateHealthBar()
{
	if (playerHealth)
	{
		auto healthPercent = playerHealth->getCurrentHitpoints() / playerHealth->getMaxHitpoints() * 100.f;

		gameNode->getEventDispatcher()->dispatchCustomEvent("setHealthBar", &healthPercent);
	}
}