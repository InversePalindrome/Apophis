/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AudioSystem.cpp
InversePalindrome.com
*/


#include "AudioSystem.hpp"
#include "AppSettings.hpp"

#include <cocos/audio/include/AudioEngine.h>


void AudioSystem::configure(entityx::EventManager& eventManager) 
{
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
		cocos2d::experimental::AudioEngine::stop(sound->getSoundID());
	}
}

void AudioSystem::receive(const entityx::ComponentRemovedEvent<SoundComponent>& event)
{
	cocos2d::experimental::AudioEngine::stop(event.component->getSoundID());
}

void AudioSystem::receive(const StateChanged& event)
{
	if (auto sound = event.entity.component<SoundComponent>(); sound && sound->hasSound(event.state))
	{
		const auto& [file, loop] = sound->getSound(event.state);

		cocos2d::experimental::AudioEngine::stop(sound->getSoundID());
		sound->setSoundID(cocos2d::experimental::AudioEngine::play2d(file, loop, AppSettings::getInstance().getSoundVolume()));
	}
}