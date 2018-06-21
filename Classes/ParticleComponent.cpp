/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const pugi::xml_node& componentNode) :
	emitter(cocos2d::ParticleSystemQuad::create(std::string(componentNode.text().as_string()) + ".plist"))
{
	emitter->retain();
}

ParticleComponent::~ParticleComponent()
{
    emitter->removeFromParent();
	emitter->removeAllChildren();

    emitter->release();
}

cocos2d::ParticleSystemQuad* ParticleComponent::getEmitter()
{
	return emitter;
}

cocos2d::ParticleSystemQuad* ParticleComponent::getEmitter() const
{
	return emitter;
}

void ParticleComponent::setPosition(const cocos2d::Vec2& position)
{
	emitter->setPosition(position);
}

void ParticleComponent::setRotation(float angle)
{
	emitter->setRotation(angle);
}

cocos2d::ParticleSystem::Mode ParticleComponent::getMode() const
{
	return emitter->getEmitterMode();
}

void ParticleComponent::setMode(cocos2d::ParticleSystem::Mode mode)
{
	emitter->setEmitterMode(mode);
}

float ParticleComponent::getDuration() const
{
	return emitter->getDuration();
}

void ParticleComponent::setDuration(float duration)
{
	emitter->setDuration(duration);
}

float ParticleComponent::getTangentialAcceleration() const
{
	return emitter->getTangentialAccel();
}

void ParticleComponent::setTangentialAcceleration(float tangentialAcceleration)
{
	emitter->setTangentialAccel(tangentialAcceleration);
}

float ParticleComponent::getStartRadius() const
{
	return emitter->getStartRadius();
}

void ParticleComponent::setStartRadius(float startRadius)
{
	emitter->setStartRadius(startRadius);
}