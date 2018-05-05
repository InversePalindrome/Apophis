/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AudioSystem.cpp
InversePalindrome.com
*/


#include "AudioSystem.hpp"
#include "AudioManager.hpp"
#include "SoundComponent.hpp"


void AudioSystem::configure(entityx::EventManager& eventManager) 
{
	eventManager.subscribe<PlayAction>(*this);
}

void AudioSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	
}

void AudioSystem::receive(const PlayAction& event)
{
	auto sound = event.entity.component<SoundComponent>();

	if (sound && sound->hasSound(event.action))
	{
		AudioManager::getInstance().playSound(sound->getSound(event.action).c_str(), event.loop);
	}
}