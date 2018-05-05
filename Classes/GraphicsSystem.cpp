/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - GraphicsSystem.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "BodyComponent.hpp"
#include "GraphicsSystem.hpp"
#include "AnimationComponent.hpp"

#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCActionInterval.h>


GraphicsSystem::GraphicsSystem(cocos2d::Node* mainNode, Map& map) :
	mainNode(mainNode),
	map(map)
{
}

void GraphicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::ComponentAddedEvent<NodeComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<SpriteComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<LabelComponent>>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<ParticleComponent>>(*this);
	eventManager.subscribe<SetPosition>(*this);
	eventManager.subscribe<SetRotation>(*this);
	eventManager.subscribe<CreateTransform>(*this);
	eventManager.subscribe<PlayAction>(*this);
}

void GraphicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<NodeComponent> node;
	entityx::ComponentHandle<BodyComponent> body;

	for (auto entity : entityManager.entities_with_components(node, body))
	{
		node->getNode()->setPosition({ body->getPosition().x * PTM_RATIO, body->getPosition().y * PTM_RATIO });
	   	node->getNode()->setRotation(CC_RADIANS_TO_DEGREES(body->getAngle()));

	    if (entity.has_component<Player>())
		{
			moveView(node->getNode()->getPosition());
		}
	}
}

void GraphicsSystem::receive(const entityx::ComponentAddedEvent<NodeComponent>& event)
{
	mainNode->addChild(event.component->getNode());
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

void GraphicsSystem::receive(const SetPosition& event)
{
	if (auto node = event.entity.component<NodeComponent>())
	{
		node->getNode()->setPosition({ event.position.x * PTM_RATIO, event.position.y * PTM_RATIO });
	}
}

void GraphicsSystem::receive(const SetRotation& event)
{
	if (auto node = event.entity.component<NodeComponent>())
	{
		node->getNode()->setRotation(CC_RADIANS_TO_DEGREES(event.angle));
	}
}

void GraphicsSystem::receive(const CreateTransform& event)
{
	auto childNode = event.childEntity.component<NodeComponent>();
	auto parentNode = event.parentEntity.component<NodeComponent>();

	if (childNode && parentNode)
	{
		childNode->getNode()->removeFromParent();
		parentNode->getNode()->addChild(childNode->getNode());
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

void GraphicsSystem::moveView(const cocos2d::Vec2& focusPoint)
{
	const auto& worldPoint = mainNode->convertToWorldSpace(focusPoint);
	const auto& windowSize = cocos2d::Director::getInstance()->getWinSize();

	if (std::abs(focusPoint.x) < map.getDimensions().x * PTM_RATIO / 2.f - windowSize.width / 2.f)
	{
		mainNode->setPositionX(mainNode->getPosition().x - worldPoint.x + windowSize.width / 2.f);
    }
	if (std::abs(focusPoint.y) < map.getDimensions().y  * PTM_RATIO / 2.f - windowSize.height / 2.f)
	{
		mainNode->setPositionY(mainNode->getPosition().y - worldPoint.y + windowSize.height / 2.f);
	}
}