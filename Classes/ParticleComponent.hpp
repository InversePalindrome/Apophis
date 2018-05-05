/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <cocos/2d/CCParticleSystemQuad.h>


class ParticleComponent 
{
public:
	explicit ParticleComponent(const tinyxml2::XMLElement* componentNode);

	~ParticleComponent();

	cocos2d::ParticleSystemQuad* getParticleSystem();
	cocos2d::ParticleSystemQuad* getParticleSystem() const;

private:
	cocos2d::ParticleSystemQuad* particleSystem;
};