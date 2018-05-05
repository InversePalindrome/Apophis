/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const tinyxml2::XMLElement* componentNode)  :
	particleSystem(cocos2d::ParticleSystemQuad::create())
{
	if (const auto* filename = componentNode->GetText())
	{
	    particleSystem->initWithFile(std::string(filename) + ".plist");
	}

	particleSystem->retain();
}

ParticleComponent::~ParticleComponent()
{
	particleSystem->removeFromParentAndCleanup(true);
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