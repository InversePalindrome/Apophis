/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::ParticleSystemQuad::create(std::string(componentNode.text().as_string()) + ".plist"), componentNode),
	emitter(static_cast<cocos2d::ParticleSystemQuad*>(getNode()))
{
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

cocos2d::Vec2 ParticleComponent::getGravity() const
{
	return emitter->getGravity();
}

void ParticleComponent::setGravity(const cocos2d::Vec2& gravity)
{
	emitter->setGravity(gravity);
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

float ParticleComponent::getEndRadius() const
{
	return emitter->getEndRadius();
}

void ParticleComponent::setEndRadius(float endRadius)
{
	emitter->setEndRadius(endRadius);
}