/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AudioSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"
#include "SoundComponent.hpp"

#include <entityx/System.h>


class AudioSystem : public entityx::System<AudioSystem>, public entityx::Receiver<AudioSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const entityx::EntityDestroyedEvent& event);
	virtual void receive(const entityx::ComponentRemovedEvent<SoundComponent>& event);
	virtual void receive(const PlayAction& event);
	virtual void receive(const StopAction& event);

private:
	static void stopSounds(entityx::ComponentHandle<SoundComponent> sound);
};