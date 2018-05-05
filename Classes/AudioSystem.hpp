/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AudioSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <entityx/entityx.h>

#include <cocos/audio/include/SimpleAudioEngine.h>


class AudioSystem : public entityx::System<AudioSystem>, public entityx::Receiver<AudioSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const PlayAction& event);
};