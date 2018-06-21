/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCParticleSystemQuad.h>

#include <pugixml.hpp>


class ParticleComponent 
{
public:
	explicit ParticleComponent(const pugi::xml_node& componentNode);

	~ParticleComponent();

	cocos2d::ParticleSystemQuad* getEmitter();
	cocos2d::ParticleSystemQuad* getEmitter() const;

	void setPosition(const cocos2d::Vec2& position);
	void setRotation(float angle);

	cocos2d::ParticleSystem::Mode getMode() const;
	void setMode(cocos2d::ParticleSystem::Mode mode);

	float getDuration() const;
	void setDuration(float duration);

	float getTangentialAcceleration() const;
	void setTangentialAcceleration(float tangentialAcceleration);

	float getStartRadius() const;
	void setStartRadius(float startRadius);

private:
	cocos2d::ParticleSystemQuad* emitter;
};