/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Constants.hpp"
#include "SpatialComponent.hpp"
#include "GraphicsSystem.hpp"
#include "AnimationComponent.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCActionInterval.h>
#include <cocos/base/CCEventDispatcher.h>


GraphicsSystem::GraphicsSystem(cocos2d::Node* gameNode, Map& map) :
	gameNode(gameNode),
	map(map)
{
}

void GraphicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<NodeComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<SpriteComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<LabelComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<ParticleComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<Player>>(*this);
	eventManager.subscribe<EntityDied>(*this);
	eventManager.subscribe<PlayAction>(*this);
}

void GraphicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<NodeComponent> node;
	entityx::ComponentHandle<SpatialComponent> spatial;

	for (auto entity : entityManager.entities_with_components(node, spatial))
	{
		node->setPosition({ spatial->getPosition()[0] * Constants::PTM_RATIO, spatial->getPosition()[1] * Constants::PTM_RATIO });
		node->setRotation(spatial->getAngle());
	}

	updateView();
	updateHealthBar();
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<NodeComponent>& event)
{
	gameNode->addChild(event.component->getNode());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<SpriteComponent>& event)
{
	auto entity = event.entity;

	entity.assign<NodeComponent>(event.component->getSprite());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<LabelComponent>& event)
{
	auto entity = event.entity;
	
	entity.assign<NodeComponent>(event.component->getLabel());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<ParticleComponent>& event)
{
	auto entity = event.entity;

	entity.assign<NodeComponent>(event.component->getParticleSystem());
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<Player>& event)
{
	auto player = event.entity;

	playerNode = player.component<NodeComponent>();
	playerHealth = player.component<HealthComponent>();
}

void GraphicsSystem::receive(const EntityDied& event)
{
	if (event.entity.has_component<Player>())
	{
		gameNode->getEventDispatcher()->dispatchCustomEvent("gameOver");
	}
}

void GraphicsSystem::receive(const PlayAction& event)
{
	auto node = event.entity.component<NodeComponent>();
	auto animation = event.entity.component<AnimationComponent>();

	if (node && animation && animation->hasAnimation(event.action))
	{
		if (event.loop)
		{
			node->getNode()->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation->getAnimation(event.action))));
		}
		else
		{
			node->getNode()->runAction(cocos2d::Animate::create(animation->getAnimation(event.action)));
		}
	}
}

void GraphicsSystem::updateView()
{
	if (playerNode.valid())
	{
		auto worldPoint = gameNode->convertToWorldSpace(playerNode->getPosition());
		auto windowSize = cocos2d::Director::getInstance()->getWinSize();
	
		if (std::abs(playerNode->getPosition().x) < map.getDimensions().x * Constants::PTM_RATIO / 2.f - windowSize.width / 2.f)
		{
			gameNode->setPositionX(gameNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
		}
		if (std::abs(playerNode->getPosition().y) < map.getDimensions().y * Constants::PTM_RATIO / 2.f - windowSize.height / 2.f)
		{
			gameNode->setPositionY(gameNode->getPosition().y - worldPoint.y + windowSize.height / 2.f);
		}
	}
}

void GraphicsSystem::updateHealthBar()
{
	if (playerHealth.valid())
	{
		auto healthPercent = playerHealth->getCurrentHitpoints() / playerHealth->getMaxHitpoints() * 100.f;

		gameNode->getEventDispatcher()->dispatchCustomEvent("setHealthBar", &healthPercent);
	}
}