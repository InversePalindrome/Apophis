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

	void save(pugi::xml_node& componentNode) const;

	void initWithFile(const std::string& filename);

	void setDisplayFrame(const std::string& spriteFrameName);

	cocos2d::ParticleSystem::Mode getMode() const;
	void setMode(cocos2d::ParticleSystem::Mode mode);

	float getDuration() const;
	void setDuration(float duration);

	float getEmissionRate() const;
	void setEmissionRate(float emissionRate);

	cocos2d::Vec2 getGravity() const;
	void setGravity(const cocos2d::Vec2& gravity);

	float getLife() const;
	void setLife(float life);

	float getLifeVar() const;
	void setLifeVar(float lifeVar);

	float getSpeed() const;
	void setSpeed(float speed);

	float getSpeedVar() const;
	void setSpeedVar(float speedVar);

	float getTangentialAcceleration() const;
	void setTangentialAcceleration(float tangentialAcceleration);

	float getTangentialAccelerationVar() const;
	void setTangentialAccelerationVar(float tangentialAccelerationVar);

	float getRadialAcceleration() const;
	void setRadialAcceleration(float radialAcceleration);

	float getRadialAccelerationVar() const;
	void setRadialAccelerationVar(float radialAccelerationVar);

	float getStartRadius() const;
	void setStartRadius(float startRadius);

	float getStartRadiusVar() const;
	void setStartRadiusVar(float startRadiusVar);

	float getEndRadius() const;
	void setEndRadius(float endRadius);

	float getEndRadiusVar() const;
	void setEndRadiusVar(float endRadiusVar);

	cocos2d::Color4F getStartColor() const;
	void setStartColor(const cocos2d::Color4F& startColor);

	cocos2d::Color4F getStartColorVar() const;
	void setStartColorVar(const cocos2d::Color4F& startColorVar);

	cocos2d::Color4F getEndColor() const;
	void setEndColor(const cocos2d::Color4F& endColor);

	cocos2d::Color4F getEndColorVar() const;
	void setEndColorVar(const cocos2d::Color4F& endColorVar);

private:
	cocos2d::ParticleSystemQuad* emitter;

	std::string filename;
	std::string spriteFrameName;
};