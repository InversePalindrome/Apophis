/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AudioSystem.cpp
InversePalindrome.com
*/


#include "AudioSystem.hpp"
#include "AppSettings.hpp"
#include "SoundComponent.hpp"

#include <cocos/audio/include/AudioEngine.h>


void AudioSystem::configure(entityx::EventManager& eventManager) 
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<SoundComponent>>(*this);
	eventManager.subscribe<PlayAction>(*this);
	eventManager.subscribe<StopAction>(*this);
}

void AudioSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void AudioSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto destroyedEntity = event.entity;

	if (auto sound = destroyedEntity.component<SoundComponent>())
	{
		stopSounds(sound);
	}
}

void AudioSystem::receive(const entityx::ComponentRemovedEvent<SoundComponent>& event)
{
	stopSounds(event.component);
}

void AudioSystem::receive(const PlayAction& event)
{
	auto sound = event.entity.component<SoundComponent>();

	if (sound && sound->hasSoundFile(event.action))
	{
		auto soundID = cocos2d::experimental::AudioEngine::play2d(sound->getSoundFile(event.action), event.loop, AppSettings::getInstance().getSoundVolume());

		sound->addSoundID(event.action, soundID);

		cocos2d::experimental::AudioEngine::setFinishCallback(soundID, [sound, event](auto id, const auto& filename) mutable
		{
			if (sound)
			{
				sound->removeSoundID(event.action);
			}
		});
	}
}

void AudioSystem::receive(const StopAction& event)
{
	auto sound = event.entity.component<SoundComponent>();

	if (sound && sound->hasSoundID(event.action))
	{
		cocos2d::experimental::AudioEngine::stop(sound->getSoundID(event.action));

		sound->removeSoundID(event.action);
	}
}

void AudioSystem::stopSounds(entityx::ComponentHandle<SoundComponent> sound)
{
	for (const auto& soundID : sound->getSoundIDs())
	{
		cocos2d::experimental::AudioEngine::stop(soundID.second);
	}
}