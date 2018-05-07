/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - BehaviorSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "BodyComponent.hpp"

#include <entityx/entityx.h>


class BehaviorSystem : public entityx::System<BehaviorSystem>, public entityx::Receiver<BehaviorSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const EntityCreated& event);

private:
	entityx::ComponentHandle<BodyComponent> targetBody;

	void updateSeek(entityx::Entity entity);
	void updateFlee(entityx::Entity entity);
	void updatePursue(entityx::Entity entity);
	void updateEvade(entityx::Entity entity);
	void updateArrive(entityx::Entity entity);
	void updateWander(entityx::Entity entity);
	void updatePatrol(entityx::Entity entity);
	void updateAvoid(entityx::Entity entity);
	void updateAlign(entityx::Entity entity);
	void updateCohesion(entityx::Entity entity);
	void updateSeparate(entityx::Entity entity);
	void updateFollow(entityx::Entity entity);
	void updateQueue(entityx::Entity entity);
	void updateRotation(entityx::Entity entity);
};