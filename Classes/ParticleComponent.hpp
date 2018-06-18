/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <cocos/2d/CCParticleSystemQuad.h>


class ParticleComponent 
{
public:
	explicit ParticleComponent(const pugi::xml_node& componentNode);

	~ParticleComponent();

	cocos2d::ParticleSystemQuad* getParticleSystem();
	cocos2d::ParticleSystemQuad* getParticleSystem() const;

	void setPosition(const cocos2d::Vec2& position);
	void setRotation(float angle);

private:
	cocos2d::ParticleSystemQuad* particleSystem;
};