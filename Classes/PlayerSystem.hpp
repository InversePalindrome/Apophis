/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "KeyAction.hpp"
#include "TagsComponent.hpp"
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

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const ComponentLoaded<entityx::ComponentHandle<TagsComponent>>& event);

private:
	cocos2d::Node* gameNode;

	entityx::Entity player;

	std::vector<KeyAction> keyActions;
	cocos2d::Vec2 playerFocusPoint;
	bool isShooting;

	void updateMovement(entityx::ComponentHandle<BodyComponent> body, const entityx::ComponentHandle<SpeedComponent> speed, const entityx::ComponentHandle<AccelerationComponent> acceleration);
	void updateRotation(entityx::ComponentHandle<BodyComponent> body);
	void updateShooting(entityx::EventManager& eventManager);
};