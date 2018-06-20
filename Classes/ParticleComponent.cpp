/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const pugi::xml_node& componentNode) :
	particleSystem(cocos2d::ParticleSystemQuad::create(std::string(componentNode.text().as_string()) + ".plist"))
{
	particleSystem->retain();
}

ParticleComponent::~ParticleComponent()
{
	particleSystem->removeAllChildren();
	particleSystem->removeFromParent();

	particleSystem->release();
}

cocos2d::ParticleSystemQuad* ParticleComponent::getParticleSystem()
{
	return particleSystem;
}

cocos2d::ParticleSystemQuad* ParticleComponent::getParticleSystem() const
{
	return particleSystem;
}

void ParticleComponent::setPosition(const cocos2d::Vec2& position)
{
	particleSystem->setPosition(position);
}

void ParticleComponent::setRotation(float angle)
{
	particleSystem->setRotation(angle);
}

void ParticleComponent::setScale(float xScale, float yScale)
{
}