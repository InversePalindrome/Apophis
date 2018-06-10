/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const pugi::xml_node& componentNode)  :
	particleSystem(cocos2d::ParticleSystemQuad::create())
{
	load(componentNode.text().as_string());

	particleSystem->retain();
}

ParticleComponent::~ParticleComponent()
{
	particleSystem->removeFromParentAndCleanup(true);
	particleSystem->release();
}

void ParticleComponent::load(const std::string& filename)
{
	particleSystem->initWithFile(filename + ".plist");
}

cocos2d::ParticleSystemQuad* ParticleComponent::getParticleSystem()
{
	return particleSystem;
}

cocos2d::ParticleSystemQuad* ParticleComponent::getParticleSystem() const
{
	return particleSystem;
}