/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyAction.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "ImpulseComponent.hpp"

#include <cocos/2d/CCNode.h>

#include <entityx/System.h>

#include <vector>


class PlayerSystem : public entityx::System<PlayerSystem>, public entityx::Receiver<PlayerSystem>
{
public:
	explicit PlayerSystem(cocos2d::Node* gameNode);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityParsed& event);

private:
	cocos2d::Node* gameNode;

	entityx::EventManager* eventManager;

	entityx::Entity player;
	entityx::ComponentHandle<BodyComponent> playerBody;
	entityx::ComponentHandle<SpeedComponent> playerSpeed;
	entityx::ComponentHandle<ImpulseComponent> playerImpulse;

	std::vector<KeyAction> keyActions;
	cocos2d::Vec2 playerFocusPoint;
	bool isShooting;

	void updateMovement();
	void updateRotation();
	void updateShooting();
};