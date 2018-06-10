/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCParticleSystemQuad.h>

#include <pugixml.hpp>

#include <string>


class ParticleComponent 
{
public:
	explicit ParticleComponent(const pugi::xml_node& componentNode);

	~ParticleComponent();

	void load(const std::string& filename);

	cocos2d::ParticleSystemQuad* getParticleSystem();
	cocos2d::ParticleSystemQuad* getParticleSystem() const;

private:
	cocos2d::ParticleSystemQuad* particleSystem;
};