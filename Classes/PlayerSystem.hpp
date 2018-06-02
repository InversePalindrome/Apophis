/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "MouseManager.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "KeyboardManager.hpp"

#include <entityx/System.h>


class PlayerSystem : public entityx::System<PlayerSystem>, public entityx::Receiver<PlayerSystem>
{
public:
	PlayerSystem(KeyboardManager* keyboardManager, MouseManager* mouseManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	KeyboardManager* keyboardManager;
	MouseManager* mouseManager;

	void updateMovement(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed);
	void updateRotation(entityx::ComponentHandle<BodyComponent> body);
	void updateShooting(entityx::EventManager& eventManager, entityx::Entity player);
};