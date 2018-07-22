/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyAction.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "AccelerationComponent.hpp"

#include <cocos/2d/CCNode.h>

#include <entityx/System.h>

#include <vector>


class PlayerSystem : public entityx::System<PlayerSystem>, public entityx::Receiver<PlayerSystem>
{
public:
	explicit PlayerSystem(cocos2d::Node* gameNode);

	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	cocos2d::Node* gameNode;

	std::vector<KeyAction> keyActions;
	cocos2d::Vec2 playerFocusPoint;
	bool isShooting;

	void updateMovement(BodyComponent& body, const SpeedComponent& speed, const AccelerationComponent& acceleration);
	void updateRotation(BodyComponent& body);
	void updateShooting(entityx::EventManager& eventManager, entityx::Entity entity);
};