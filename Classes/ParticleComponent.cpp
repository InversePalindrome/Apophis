/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"


ParticleComponent::ParticleComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::ParticleSystemQuad::create(), componentNode),
	emitter(static_cast<cocos2d::ParticleSystemQuad*>(getNode()))
{
	if (const auto filenameAttribute = componentNode.attribute("filename"))
	{
	     initWithFile(filenameAttribute.as_string());
	}
	if (const auto modeAttribute = componentNode.attribute("mode"))
	{
		setMode(static_cast<cocos2d::ParticleSystem::Mode>(modeAttribute.as_int()));
	}
	if (const auto durationAttribute = componentNode.attribute("duration"))
	{
		setDuration(durationAttribute.as_float());
	}
	if (const auto emissionRateAttribute = componentNode.attribute("emissionRate"))
	{
		setEmissionRate(emissionRateAttribute.as_float());
	}
	
	const auto xGravityAttribute = componentNode.attribute("xGravity");
	const auto yGravityAttribute = componentNode.attribute("yGravity");

	if (xGravityAttribute && yGravityAttribute)
	{
		setGravity({ xGravityAttribute.as_float(), yGravityAttribute.as_float() });
	}
	
	if (const auto lifeAttribute = componentNode.attribute("life"))
	{
		setLife(lifeAttribute.as_float());
	}
	if (const auto lifeVarAttribute = componentNode.attribute("lifeVar"))
	{
		setLifeVar(lifeVarAttribute.as_float());
	}
	if (const auto speedAttribute = componentNode.attribute("speed"))
	{
		setSpeed(speedAttribute.as_float());
	}
	if (const auto speedVarAttribute = componentNode.attribute("speedVar"))
	{
		setSpeedVar(speedVarAttribute.as_float());
	}
	if (const auto tangentialAccelerationAttribute = componentNode.attribute("tangentialAcceleration"))
	{
		setTangentialAcceleration(tangentialAccelerationAttribute.as_float());
	}
	if (const auto tangentialAccelerationAttribute = componentNode.attribute("tangentialAccelerationVar"))
	{
		setTangentialAccelerationVar(tangentialAccelerationAttribute.as_float());
	}
	if (const auto radialAccelerationAttribute = componentNode.attribute("radialAcceleration"))
	{
		setRadialAcceleration(radialAccelerationAttribute.as_float());
	}
	if (const auto radialAccelerationVarAttribute = componentNode.attribute("radialAccelerationVar"))
	{
		setRadialAccelerationVar(radialAccelerationVarAttribute.as_float());
	}
	if (const auto startRadiusAttribute = componentNode.attribute("startRadius"))
	{
		setStartRadius(startRadiusAttribute.as_float());
	}
	if (const auto startRadiusVarAttribute = componentNode.attribute("startRadiusVar"))
	{
		setStartRadiusVar(startRadiusVarAttribute.as_float());
	}
	if (const auto endRadiusAttribute = componentNode.attribute("endRadius"))
	{
		setEndRadius(endRadiusAttribute.as_float());
	}
	if (const auto endRadiusVarAttribute = componentNode.attribute("endRadiusVar"))
	{
		setEndRadiusVar(endRadiusVarAttribute.as_float());
	}

	const auto startColorRAttribute = componentNode.attribute("startR");
	const auto startColorGAttribute = componentNode.attribute("startG");
	const auto startColorBAttribute = componentNode.attribute("startB");
	const auto startColorAAttribute = componentNode.attribute("startA");

	if (startColorRAttribute && startColorBAttribute && startColorGAttribute && startColorAAttribute)
	{
		setStartColor(cocos2d::Color4F(startColorRAttribute.as_uint(), startColorGAttribute.as_uint(), startColorBAttribute.as_uint(), startColorAAttribute.as_uint()));
	}

	const auto startColorVarRAttribute = componentNode.attribute("startVarR");
	const auto startColorVarGAttribute = componentNode.attribute("startVarG");
	const auto startColorVarBAttribute = componentNode.attribute("startVarB");
	const auto startColorVarAAttribute = componentNode.attribute("startVarA");

	if (startColorVarRAttribute && startColorVarGAttribute && startColorVarBAttribute && startColorVarAAttribute)
	{
		setStartColorVar(cocos2d::Color4F(startColorVarRAttribute.as_uint(), startColorVarGAttribute.as_uint(), startColorVarBAttribute.as_uint(), startColorVarAAttribute.as_uint()));
	}

	const auto endColorRAttribute = componentNode.attribute("endR");
	const auto endColorGAttribute = componentNode.attribute("endG");
	const auto endColorBAttribute = componentNode.attribute("endB");
	const auto endColorAAttribute = componentNode.attribute("endA");

	if (endColorRAttribute && endColorBAttribute && endColorGAttribute && endColorAAttribute)
	{
		setEndColor(cocos2d::Color4F(endColorRAttribute.as_uint(), endColorGAttribute.as_uint(), endColorBAttribute.as_uint(), endColorAAttribute.as_uint()));
	}

	const auto endColorVarRAttribute = componentNode.attribute("endVarR");
	const auto endColorVarGAttribute = componentNode.attribute("endVarG");
	const auto endColorVarBAttribute = componentNode.attribute("endVarB");
	const auto endColorVarAAttribute = componentNode.attribute("endVarA");

	if (endColorVarRAttribute && endColorVarBAttribute && endColorVarGAttribute && endColorVarAAttribute)
	{
		setEndColorVar(cocos2d::Color4F(endColorVarRAttribute.as_uint(), endColorVarGAttribute.as_uint(), endColorVarBAttribute.as_uint(), endColorVarAAttribute.as_uint()));
	}
}

void ParticleComponent::initWithFile(const std::string& filename)
{
	emitter->initWithFile(filename + ".plist");
}

cocos2d::ParticleSystem::Mode ParticleComponent::getMode() const
{
	return emitter->getEmitterMode();
}

void ParticleComponent::setMode(cocos2d::ParticleSystem::Mode mode)
{
	emitter->setEmitterMode(mode);
}

float ParticleComponent::getDuration() const
{
	return emitter->getDuration();
}

void ParticleComponent::setDuration(float duration)
{
	emitter->setDuration(duration);
}

float ParticleComponent::getEmissionRate() const
{
	return emitter->getEmissionRate();
}

void ParticleComponent::setEmissionRate(float emissionRate)
{
	emitter->setEmissionRate(emissionRate);
}

cocos2d::Vec2 ParticleComponent::getGravity() const
{
	return emitter->getGravity();
}

void ParticleComponent::setGravity(const cocos2d::Vec2& gravity)
{
	emitter->setGravity(gravity);
}

float ParticleComponent::getLife() const
{
	return emitter->getLife();
}

void ParticleComponent::setLife(float life)
{
	emitter->setLife(life);
}

float ParticleComponent::getLifeVar() const
{
	return emitter->getLifeVar();
}

void ParticleComponent::setLifeVar(float lifeVar)
{
	emitter->setLifeVar(lifeVar);
}

float ParticleComponent::getSpeed() const
{
	return emitter->getSpeed();
}

void ParticleComponent::setSpeed(float speed)
{
	emitter->setSpeed(speed);
}

float ParticleComponent::getSpeedVar() const
{
	return emitter->getSpeedVar();
}

void ParticleComponent::setSpeedVar(float speedVar)
{
	emitter->setSpeedVar(speedVar);
}

float ParticleComponent::getTangentialAcceleration() const
{
	return emitter->getTangentialAccel();
}

void ParticleComponent::setTangentialAcceleration(float tangentialAcceleration)
{
	emitter->setTangentialAccel(tangentialAcceleration);
}

float ParticleComponent::getTangentialAccelerationVar() const
{
	return emitter->getTangentialAccelVar();
}

void ParticleComponent::setTangentialAccelerationVar(float tangentialAccelerationVar)
{
	emitter->setTangentialAccelVar(tangentialAccelerationVar);
}

float ParticleComponent::getRadialAcceleration() const
{
	return emitter->getRadialAccel();
}

void ParticleComponent::setRadialAcceleration(float radialAcceleration)
{
	emitter->setRadialAccel(radialAcceleration);
}

float ParticleComponent::getRadialAccelerationVar() const
{
	return emitter->getRadialAccelVar();
}

void ParticleComponent::setRadialAccelerationVar(float radialAccelerationVar)
{
	emitter->setRadialAccelVar(radialAccelerationVar);
}

float ParticleComponent::getStartRadius() const
{
	return emitter->getStartRadius();
}

void ParticleComponent::setStartRadius(float startRadius)
{
	emitter->setStartRadius(startRadius);
}

float ParticleComponent::getStartRadiusVar() const
{
	return emitter->getStartRadiusVar();
}
void ParticleComponent::setStartRadiusVar(float startRadiusVar)
{
	emitter->setStartRadiusVar(startRadiusVar);
}

float ParticleComponent::getEndRadius() const
{
	return emitter->getEndRadius();
}

void ParticleComponent::setEndRadius(float endRadius)
{
	emitter->setEndRadius(endRadius);
}

float ParticleComponent::getEndRadiusVar() const
{
	return emitter->getEndRadiusVar();
}

void ParticleComponent::setEndRadiusVar(float endRadiusVar)
{
	emitter->setEndRadiusVar(endRadiusVar);
}

cocos2d::Color4F ParticleComponent::getStartColor() const
{
	return emitter->getStartColor();
}

void ParticleComponent::setStartColor(const cocos2d::Color4F& startColor)
{
	emitter->setStartColor(startColor);
}

cocos2d::Color4F ParticleComponent::getStartColorVar() const
{
	return emitter->getStartColorVar();
}

void ParticleComponent::setStartColorVar(const cocos2d::Color4F& startColorVar)
{
	emitter->setStartColorVar(startColorVar);
}

cocos2d::Color4F ParticleComponent::getEndColor() const
{
	return emitter->getEndColor();
}

void ParticleComponent::setEndColor(const cocos2d::Color4F& endColor)
{
	emitter->setEndColor(endColor);
}

cocos2d::Color4F ParticleComponent::getEndColorVar() const
{
	return emitter->getEndColorVar();
}

void ParticleComponent::setEndColorVar(const cocos2d::Color4F& endColorVar)
{
	emitter->setEndColorVar(endColorVar);
}