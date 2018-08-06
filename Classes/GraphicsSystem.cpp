/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "Renderables.hpp"
#include "GraphicsSystem.hpp"
#include "PlayerComponent.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>

#include <brigand/algorithms/for_each.hpp>


GraphicsSystem::GraphicsSystem(cocos2d::Node* gameNode, const b2Vec2& mapDimensions) :
	gameNode(gameNode),
	mapDimensions(mapDimensions)
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

	updateNodeCallbacks();
	updateView();
	updateHealthBar();
}

void GraphicsSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<PlayerComponent>())
	{
		playerTransform = event.entity.component<TransformComponent>();
		playerHealth = event.entity.component<HealthComponent>();
	}
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<SpriteComponent>& event)
{
	nodeCallbacks.push_back([this, event]()
	{
		if (event.component)
		{
			gameNode->addChild(event.component->getNode());
		}
	});
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<LabelComponent>& event)
{
	nodeCallbacks.push_back([this, event]()
	{ 
		if (event.component)
		{
			gameNode->addChild(event.component->getNode());
		}
	});
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<ParticleComponent>& event)
{
	nodeCallbacks.push_back([this, event]() 
	{ 
		if (event.component)
		{
			gameNode->addChild(event.component->getNode());
		}
	});
}

void GraphicsSystem::updateNodeCallbacks()
{
	for (const auto& nodeCallback : nodeCallbacks)
	{
		nodeCallback();
	}

	nodeCallbacks.clear();
}

void GraphicsSystem::updateView()
{
	if (playerTransform)
	{
		const auto playerNodePosition = cocos2d::Vec2(playerTransform->getPosition().x * Constants::PTM_RATIO, playerTransform->getPosition().y * Constants::PTM_RATIO);
		const auto worldPoint = gameNode->convertToWorldSpace(playerNodePosition);
		const auto windowSize = cocos2d::Director::getInstance()->getWinSize();
		
		if (std::abs(playerNodePosition.x) < mapDimensions.x * Constants::PTM_RATIO / 2.f - windowSize.width / 2.f)
		{
			gameNode->setPositionX(gameNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
		}
		if (std::abs(playerNodePosition.y) < mapDimensions.y * Constants::PTM_RATIO / 2.f - windowSize.height / 2.f)
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