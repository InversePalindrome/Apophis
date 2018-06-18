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
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<SoundComponent>>(*this);
	eventManager.subscribe<PlayAudio>(*this);
	eventManager.subscribe<StopAudio>(*this);
	eventManager.subscribe<StopAllAudio>(*this);
}

void AudioSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void AudioSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto destroyedEntity = event.entity;

	if (auto sound = destroyedEntity.component<SoundComponent>())
	{
		stopAllSounds(sound);
	}
}

void AudioSystem::receive(const entityx::ComponentRemovedEvent<SoundComponent>& event)
{
	stopAllSounds(event.component);
}

void AudioSystem::receive(const PlayAudio& event)
{
	auto sound = event.entity.component<SoundComponent>();

	if (sound && sound->hasSoundFile(event.sound))
	{
		auto soundID = cocos2d::experimental::AudioEngine::play2d(sound->getSoundFile(event.sound), event.loop, AppSettings::getInstance().getSoundVolume());

		sound->addSoundID(event.sound, soundID);

		cocos2d::experimental::AudioEngine::setFinishCallback(soundID, [sound, event](auto id, const auto& filename) mutable
		{
			if (sound && sound->hasSoundID(event.sound))
			{
				sound->removeSoundID(event.sound);
			}
		});
	}
}

void AudioSystem::receive(const StopAudio& event)
{
	auto sound = event.entity.component<SoundComponent>();

	if (sound && sound->hasSoundID(event.sound))
	{
		cocos2d::experimental::AudioEngine::stop(sound->getSoundID(event.sound));

		sound->removeSoundID(event.sound);
	}
}

void AudioSystem::receive(const StopAllAudio& event)
{
	if (auto sound = event.entity.component<SoundComponent>())
	{
		stopAllSounds(sound);
	}
}

void AudioSystem::stopAllSounds(entityx::ComponentHandle<SoundComponent> sound)
{
	for (const auto& soundID : sound->getSoundIDs())
	{
		cocos2d::experimental::AudioEngine::stop(soundID.second);
	}

	sound->clearSoundIDs();
}