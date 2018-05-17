/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const tinyxml2::XMLElement* componentNode)  :
	particleSystem(cocos2d::ParticleSystemQuad::create())
{
	if (const auto* filename = componentNode->GetText())
	{
	    load(filename);
	}

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