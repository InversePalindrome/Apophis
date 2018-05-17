/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <cocos/2d/CCParticleSystemQuad.h>

#include <string>


class ParticleComponent 
{
public:
	explicit ParticleComponent(const tinyxml2::XMLElement* componentNode);

	~ParticleComponent();

	void load(const std::string& filename);

	cocos2d::ParticleSystemQuad* getParticleSystem();
	cocos2d::ParticleSystemQuad* getParticleSystem() const;

private:
	cocos2d::ParticleSystemQuad* particleSystem;
};