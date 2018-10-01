/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AudioSystem.cpp
InversePalindrome.com
*/


#include "AudioSystem.hpp"
#include "AppSettings.hpp"


void AudioSystem::configure(entityx::EventManager& eventManager) 
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<SoundComponent>>(*this);
	eventManager.subscribe<StateChanged>(*this);
}

void AudioSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void AudioSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto sound = entity.component<SoundComponent>())
	{
		AppSettings::getInstance().stopSound(sound->getSoundID());
	}
}

void AudioSystem::receive(const entityx::ComponentRemovedEvent<SoundComponent>& event)
{
	AppSettings::getInstance().stopSound(event.component->getSoundID());
}

void AudioSystem::receive(const StateChanged& event)
{
	if (auto sound = event.entity.component<SoundComponent>(); sound && sound->hasSound(event.state))
	{
		const auto& [file, loop] = sound->getSound(event.state);

		AppSettings::getInstance().stopSound(sound->getSoundID());
		sound->setSoundID(AppSettings::getInstance().playSound(file, loop));
	}
}