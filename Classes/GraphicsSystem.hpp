/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - GraphicsSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "Tags.hpp"
#include "Events.hpp" 
#include "HudNode.hpp"
#include "NodeComponent.hpp"
#include "LabelComponent.hpp"
#include "HealthComponent.hpp"
#include "SpriteComponent.hpp"
#include "ParticleComponent.hpp"

#include <entityx/System.h>

#include <cocos/2d/CCNode.h>


class GraphicsSystem : public entityx::System<GraphicsSystem>, public entityx::Receiver<GraphicsSystem>
{
public:
	GraphicsSystem(cocos2d::Node* gameNode, HudNode* hudNode, Map& map);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::ComponentAddedEvent<NodeComponent>& event);
	virtual void receive(const entityx::ComponentAddedEvent<SpriteComponent>& event);
	virtual void receive(const entityx::ComponentAddedEvent<LabelComponent>& event);
	virtual void receive(const entityx::ComponentAddedEvent<ParticleComponent>& event);
	virtual void receive(const EntityCreated& event);
	virtual void receive(const SetPosition& event);
	virtual void receive(const SetRotation& event);
	virtual void receive(const CreateTransform& event);
	virtual void receive(const PlayAction& event);
	
private:
	cocos2d::Node* gameNode;
	HudNode* hudNode;

	Map& map;

	entityx::ComponentHandle<NodeComponent> playerNode;
	entityx::ComponentHandle<HealthComponent> playerHealth;

	void updateView();
	void updateHealthBar();
};