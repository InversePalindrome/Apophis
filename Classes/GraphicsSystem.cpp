/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Constants.hpp"
#include "GraphicsSystem.hpp"
#include "GeometryComponent.hpp"
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
	eventManager.subscribe<entityx::ComponentAddedEvent<SceneNodeComponent>>(*this); 
	eventManager.subscribe<EntityParsed>(*this);
}

void GraphicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<SceneNodeComponent> node; 
	entityx::ComponentHandle<GeometryComponent> geometry;

	for (auto entity : entityManager.entities_with_components(node, geometry))
	{
		node->setRootSceneNodePosition({ geometry->getPosition().x * Constants::PTM_RATIO, geometry->getPosition().y * Constants::PTM_RATIO });
		node->setRootSceneNodeRotation(geometry->getAngle());
	}
	
	updateView();
	updateHealthBar();
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<SceneNodeComponent>& event)
{
	gameNode->addChild(event.component->getRootSceneNode());
}

void GraphicsSystem::receive(const EntityParsed& event)
{
	if (event.entity.has_component<Player>())
	{
		playerNode = event.entity.component<SceneNodeComponent>();
		playerHealth = event.entity.component<HealthComponent>();
	}
}

void GraphicsSystem::updateView()
{
	if (playerNode)
	{
		const auto worldPoint = gameNode->convertToWorldSpace(playerNode->getRootSceneNodePosition());
		const auto windowSize = cocos2d::Director::getInstance()->getWinSize();
	
		if (std::abs(playerNode->getRootSceneNodePosition().x) < map.getDimensions().x * Constants::PTM_RATIO / 2.f - windowSize.width / 2.f)
		{
			gameNode->setPositionX(gameNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
		}
		if (std::abs(playerNode->getRootSceneNodePosition().y) < map.getDimensions().y * Constants::PTM_RATIO / 2.f - windowSize.height / 2.f)
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