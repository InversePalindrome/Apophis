/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "Renderables.hpp"
#include "GraphicsSystem.hpp"
#include "HealthComponent.hpp"
#include "GeometryComponent.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>

#include <brigand/algorithms/for_each.hpp>


GraphicsSystem::GraphicsSystem(cocos2d::Node* gameNode, Map& map) :
	gameNode(gameNode),
	map(map)
{
}

void GraphicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<Player>>(*this);
	eventManager.subscribe<EntityParsed>(*this);
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
			renderable->setRotation(-geometry->getAngle());
		}
	});
	
	addNodes();

	if (player)
	{
		updateView();
		updateHealthBar();
	}
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<Player>& event)
{
	player = event.entity;
}

void GraphicsSystem::receive(const EntityParsed& event)
{
	brigand::for_each<Renderables>([this, event](auto renderableElement)
	{
		using RenderableComponent = decltype(renderableElement)::type;

		auto renderable = event.entity.component<RenderableComponent>();

		renderablesToAdd.push_back([this, renderable]() 
		{ 
			if (renderable)
			{
				gameNode->addChild(renderable->getNode());
			}
		});
	});
}

void GraphicsSystem::addNodes()
{
	for (const auto renderableToAdd : renderablesToAdd)
	{
		renderableToAdd();
	}
	
	renderablesToAdd.clear();
}

void GraphicsSystem::updateView()
{
	if (auto playerGeometry = player.component<GeometryComponent>())
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
	if (auto playerHealth = player.component<HealthComponent>())
	{
		auto healthPercent = playerHealth->getCurrentHitpoints() / playerHealth->getMaxHitpoints() * 100.f;

		gameNode->getEventDispatcher()->dispatchCustomEvent("setHealthBar", &healthPercent);
	}
}