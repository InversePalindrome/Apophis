/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParticleComponent.cpp
InversePalindrome.com
*/


#include "ParticleComponent.hpp"

#include <imgui.h>

#include <cocos/2d/CCSpriteFrameCache.h>

#include <nfd.h>


ParticleComponent::ParticleComponent() :
	NodeComponent(cocos2d::ParticleSystemQuad::create()),
	emitter(static_cast<cocos2d::ParticleSystemQuad*>(getNode()))
{
}

void ParticleComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto filenameAttribute = componentNode.attribute("filename"))
	{
		initWithFile(filenameAttribute.as_string());
	}
	if (const auto spriteFrameName = componentNode.attribute("frame"))
	{
		setDisplayFrame(spriteFrameName.as_string());
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
	if (const auto lifeAttribute = componentNode.attribute("life"))
	{
		setLife(lifeAttribute.as_float());
	}
	if (const auto lifeVarAttribute = componentNode.attribute("lifeVar"))
	{
		setLifeVar(lifeVarAttribute.as_float());
	}
	if (getMode() == cocos2d::ParticleSystem::Mode::GRAVITY)
	{
		if (const auto xGravityAttribute = componentNode.attribute("xGravity"),
			yGravityAttribute = componentNode.attribute("yGravity");
		xGravityAttribute && yGravityAttribute)
		{
			setGravity({ xGravityAttribute.as_float(), yGravityAttribute.as_float() });
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
	}
	else if (getMode() == cocos2d::ParticleSystem::Mode::RADIUS)
	{
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
	}

	if (const auto startColorRAttribute = componentNode.attribute("startR"),
		startColorGAttribute = componentNode.attribute("startG"),
		startColorBAttribute = componentNode.attribute("startB"),
		startColorAAttribute = componentNode.attribute("startA");
	    startColorRAttribute && startColorBAttribute && startColorGAttribute && startColorAAttribute)
	{
		setStartColor(cocos2d::Color4F(startColorRAttribute.as_uint(), startColorGAttribute.as_uint(), startColorBAttribute.as_uint(), startColorAAttribute.as_uint()));
	}
	if (const auto startColorVarRAttribute = componentNode.attribute("startVarR"),
		startColorVarGAttribute = componentNode.attribute("startVarG"),
		startColorVarBAttribute = componentNode.attribute("startVarB"),
		startColorVarAAttribute = componentNode.attribute("startVarA");
	    startColorVarRAttribute && startColorVarGAttribute && startColorVarBAttribute && startColorVarAAttribute)
	{
		setStartColorVar(cocos2d::Color4F(startColorVarRAttribute.as_uint(), startColorVarGAttribute.as_uint(), startColorVarBAttribute.as_uint(), startColorVarAAttribute.as_uint()));
	}
	if (const auto endColorRAttribute = componentNode.attribute("endR"),
		endColorGAttribute = componentNode.attribute("endG"),
		endColorBAttribute = componentNode.attribute("endB"),
		endColorAAttribute = componentNode.attribute("endA");
	    endColorRAttribute && endColorBAttribute && endColorGAttribute && endColorAAttribute)
	{
		setEndColor(cocos2d::Color4F(endColorRAttribute.as_uint(), endColorGAttribute.as_uint(), endColorBAttribute.as_uint(), endColorAAttribute.as_uint()));
	}
	if (const auto endColorVarRAttribute = componentNode.attribute("endVarR"),
		endColorVarGAttribute = componentNode.attribute("endVarG"),
		endColorVarBAttribute = componentNode.attribute("endVarB"),
		endColorVarAAttribute = componentNode.attribute("endVarA");
	    endColorVarRAttribute && endColorVarBAttribute && endColorVarGAttribute && endColorVarAAttribute)
	{
		setEndColorVar(cocos2d::Color4F(endColorVarRAttribute.as_uint(), endColorVarGAttribute.as_uint(), endColorVarBAttribute.as_uint(), endColorVarAAttribute.as_uint()));
	}
}

void ParticleComponent::save(pugi::xml_node& componentNode) const
{
	NodeComponent::save(componentNode);

	componentNode.set_name("Particle");

	if (!filename.empty())
	{
		componentNode.append_attribute("filename") = filename.c_str();
	}

	if (!spriteFrameName.empty())
	{
		componentNode.append_attribute("frame") = spriteFrameName.c_str();
	}

	componentNode.append_attribute("mode") = static_cast<int>(getMode());
	componentNode.append_attribute("duration") = getDuration();
	componentNode.append_attribute("emissionRate") = getEmissionRate();
	componentNode.append_attribute("life") = getLife();
	componentNode.append_attribute("lifeVar") = getLifeVar();

	if (getMode() == cocos2d::ParticleSystem::Mode::GRAVITY)
	{
		componentNode.append_attribute("xGravity") = getGravity().x;
		componentNode.append_attribute("yGravity") = getGravity().y;
		componentNode.append_attribute("speed") = getSpeed();
		componentNode.append_attribute("speedVar") = getSpeedVar();
		componentNode.append_attribute("tangentialAcceleration") = getTangentialAcceleration();
		componentNode.append_attribute("tangentialAccelerationVar") = getTangentialAccelerationVar();
		componentNode.append_attribute("radialAcceleration") = getRadialAcceleration();
		componentNode.append_attribute("radialAccelerationVar") = getRadialAccelerationVar();
	}
	else if (getMode() == cocos2d::ParticleSystem::Mode::RADIUS)
	{
		componentNode.append_attribute("startRadius") = getStartRadius();
		componentNode.append_attribute("startRadiusVar") = getStartRadiusVar();
		componentNode.append_attribute("endRadius") = getEndRadius();
		componentNode.append_attribute("endRadiusVar") = getEndRadiusVar();
	}
		
	componentNode.append_attribute("startR") = getStartColor().r;
	componentNode.append_attribute("startG") = getStartColor().g;
	componentNode.append_attribute("startB") = getStartColor().b;
	componentNode.append_attribute("startA") = getStartColor().a;
	componentNode.append_attribute("starVartR") = getStartColorVar().r;
	componentNode.append_attribute("startVarG") = getStartColorVar().g;
	componentNode.append_attribute("startVarB") = getStartColorVar().b;
	componentNode.append_attribute("startVarA") = getStartColorVar().a;
	componentNode.append_attribute("endR") = getEndColor().r;
	componentNode.append_attribute("endG") = getEndColor().g;
	componentNode.append_attribute("endB") = getEndColor().b;
	componentNode.append_attribute("endA") = getEndColor().a;
	componentNode.append_attribute("endVarR") = getEndColorVar().r;
	componentNode.append_attribute("endVarG") = getEndColorVar().g;
	componentNode.append_attribute("endVarB") = getEndColorVar().b;
	componentNode.append_attribute("endVarA") = getEndColorVar().a;
}

void ParticleComponent::display()
{
	if (ImGui::TreeNode("Particle"))
	{
		ImGui::SameLine();
		if (ImGui::Button("Init With File"))
		{
			nfdchar_t* filename = nullptr;

			if (NFD_OpenDialog("plist", nullptr, &filename) == NFD_OKAY)
			{
				initWithFile(filename);
			}
		}

		NodeComponent::display();

		const char* modes[] = { "Gravity", "Radius" };

		if (auto mode = static_cast<int>(getMode()); ImGui::Combo("Mode", &mode, modes, 2))
		{
			setMode(static_cast<cocos2d::ParticleSystem::Mode>(mode));
		}
		
		if (auto duration = getDuration(); ImGui::InputFloat("Duration", &duration))
		{
			setDuration(duration);
		}

		if (auto emissionRate = getEmissionRate(); ImGui::InputFloat("Emission Rate", &emissionRate))
		{
			setEmissionRate(emissionRate);
		}

		if (auto life = getLife(); ImGui::InputFloat("Life", &life))
		{
			setLife(life);
		}
		ImGui::SameLine();
		if (auto lifeVar = getLifeVar(); ImGui::InputFloat("Life Variance", &lifeVar))
		{
			setLifeVar(lifeVar);
		}

		if (getMode() == cocos2d::ParticleSystem::Mode::GRAVITY)
		{
			if (auto gravity = getGravity(); ImGui::InputFloat2("Gravity", &gravity.x))
			{
				setGravity(gravity);
			}
			if (auto speed = getSpeed(); ImGui::InputFloat("Speed", &speed))
			{
				setSpeed(speed);
			}
			ImGui::SameLine();
			if (auto speedVar = getSpeedVar(); ImGui::InputFloat("Speed Variance", &speedVar))
			{
				setSpeedVar(speedVar);
			}
			if (auto tangentialAcceleration = getTangentialAcceleration(); ImGui::InputFloat("Tangential  Acceleration", &tangentialAcceleration))
			{
				setTangentialAcceleration(tangentialAcceleration);
			}
			ImGui::SameLine();
			if (auto tangentialAccelerationVar = getTangentialAccelerationVar(); ImGui::InputFloat("Tangential Acceleration Variance", &tangentialAccelerationVar))
			{
				setTangentialAccelerationVar(tangentialAccelerationVar);
			}
			if (auto radialAcceleration = getRadialAcceleration(); ImGui::InputFloat("Radial Acceleration", &radialAcceleration))
			{
				setRadialAcceleration(radialAcceleration);
			}
			ImGui::SameLine();
			if (auto radialAccelerationVar = getRadialAccelerationVar(); ImGui::InputFloat("Radial Acceleration Variance", &radialAccelerationVar))
			{
				setRadialAccelerationVar(radialAccelerationVar);
			}
		}
		else if (getMode() == cocos2d::ParticleSystem::Mode::RADIUS)
		{
			if (auto startRadius = getStartRadius(); ImGui::InputFloat("Start Radius", &startRadius))
			{
				setStartRadius(startRadius);
			}
			ImGui::SameLine();
			if (auto startRadiusVar = getStartRadiusVar(); ImGui::InputFloat("Start Radius Variance", &startRadiusVar))
			{
				setStartRadiusVar(startRadiusVar);
			}
			if (auto endRadius = getEndRadius(); ImGui::InputFloat("End Radius", &endRadius))
			{
				setEndRadius(endRadius);
			}
			ImGui::SameLine();
			if (auto endRadiusVar = getEndRadiusVar(); ImGui::InputFloat("End Radius Var", &endRadiusVar))
			{
				setEndRadius(endRadiusVar);
			}
		}

		if (auto startColor = getStartColor(); ImGui::ColorEdit4("Start Color", &startColor.r))
		{
			setStartColor(startColor);
		}
		if (auto startColorVar = getStartColorVar(); ImGui::ColorEdit4("Start Color Variance", &startColorVar.r))
		{
			setStartColorVar(startColorVar);
		}
		if (auto endColor = getEndColor(); ImGui::ColorEdit4("End Color", &endColor.r))
		{
			setEndColor(endColor);
		}
		if (auto endColorVar = getEndColorVar(); ImGui::ColorEdit4("End Color Variance", &endColorVar.r))
		{
			setEndColorVar(endColorVar);
		}
		
		ImGui::TreePop();
	}
}

void ParticleComponent::initWithFile(const std::string& filename)
{
	this->filename = filename;

	emitter->initWithFile(filename);
}

void ParticleComponent::setDisplayFrame(const std::string& spriteFrameName)
{
	this->spriteFrameName = spriteFrameName;

	emitter->setDisplayFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName));
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

cocos2d::Vec2 ParticleComponent::getGravity() const
{
	return emitter->getGravity();
}

void ParticleComponent::setGravity(const cocos2d::Vec2& gravity)
{
	emitter->setGravity(gravity);
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