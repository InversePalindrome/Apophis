/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GraphicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Events.hpp" 
#include "LabelComponent.hpp"
#include "SpriteComponent.hpp"
#include "HealthComponent.hpp"
#include "ParticleComponent.hpp"
#include "TransformComponent.hpp"

#include <cocos/2d/CCNode.h>

#include <entityx/System.h>

#include <vector>
#include <functional>


class GraphicsSystem : public entityx::System<GraphicsSystem>, public entityx::Receiver<GraphicsSystem>
{
public:
	GraphicsSystem(cocos2d::Node* gameNode, Map& map);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);
	virtual void receive(const entityx::ComponentAddedEvent<SpriteComponent>& event);
	virtual void receive(const entityx::ComponentAddedEvent<LabelComponent>& event);
	virtual void receive(const entityx::ComponentAddedEvent<ParticleComponent>& event);
	
private:
	cocos2d::Node* gameNode;

	std::vector<std::function<void()>> nodeCallbacks;

	Map& map;

	entityx::ComponentHandle<TransformComponent> playerTransform;
	entityx::ComponentHandle<HealthComponent> playerHealth;

	void updateNodeCallbacks();
	void updateView();
	void updateHealthBar();
};