/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "NodeComponent.hpp"

#include <cocos/2d/CCParticleSystemQuad.h>

#include <pugixml.hpp>


class ParticleComponent : public NodeComponent
{
public:
	explicit ParticleComponent(const pugi::xml_node& componentNode);

	cocos2d::ParticleSystem::Mode getMode() const;
	void setMode(cocos2d::ParticleSystem::Mode mode);

	float getDuration() const;
	void setDuration(float duration);

	cocos2d::Vec2 getGravity() const;
	void setGravity(const cocos2d::Vec2& gravity);

	float getTangentialAcceleration() const;
	void setTangentialAcceleration(float tangentialAcceleration);

	float getStartRadius() const;
	void setStartRadius(float startRadius);

	float getEndRadius() const;
	void setEndRadius(float endRadius);

private:
	cocos2d::ParticleSystemQuad* emitter;
};