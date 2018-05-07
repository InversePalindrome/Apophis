/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - EntityFactory.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "EntityFactory.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "LabelComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "SpriteComponent.hpp"
#include "WeaponComponent.hpp"
#include "ArriveComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "PredictComponent.hpp"
#include "HitpointComponent.hpp"
#include "ParticleComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


EntityFactory::EntityFactory(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	entityManager(entityManager),
	eventManager(eventManager)
{
	parsers["Player"] = [](auto entity, const auto* componentNode) { entity.assign<Player>(); };
	parsers["AI"] = [](auto entity, const auto* componentNode) { entity.assign<AI>(); };
	parsers["Seek"] = [](auto entity, const auto* componentNode) { entity.assign<SeekComponent>(); };
	parsers["Flee"] = [](auto entity, const auto* componentNode) { entity.assign<FleeComponent>(); };
	parsers["Align"] = [](auto entity, const auto* componentNode) { entity.assign<AlignComponent>(); };
	parsers["Cohesion"] = [](auto entity, const auto* componentNode) { entity.assign<CohesionComponent>(); };
	parsers["Separate"] = [](auto entity, const auto* componentNode) { entity.assign<SeparateComponent>(); };
	parsers["Pursue"] = [](auto entity, const auto* componentNode) { entity.assign<PursueComponent>(componentNode); };
	parsers["Evade"] = [](auto entity, const auto* componentNode) { entity.assign<EvadeComponent>(componentNode); };
	parsers["Avoid"] = [](auto entity, const auto* componentNode) { entity.assign<AvoidComponent>(componentNode); };
	parsers["Arrive"] = [](auto entity, const auto* componentNode) { entity.assign<ArriveComponent>(componentNode); };
	parsers["Wander"] = [](auto entity, const auto* componentNode) { entity.assign<WanderComponent>(componentNode); };
	parsers["Patrol"] = [](auto entity, const auto* componentNode) { entity.assign<PatrolComponent>(componentNode); };
	parsers["Flock"] = [](auto entity, const auto* componentNode) { entity.assign<FlockComponent>(componentNode); };
	parsers["Follow"] = [](auto entity, const auto* componentNode) { entity.assign<FollowComponent>(componentNode); };
	parsers["Queue"] = [](auto entity, const auto* componentNode) { entity.assign<QueueComponent>(componentNode); };
	parsers["Body"] = [&eventManager](auto entity, const auto* componentNode) { eventManager.emit(CreateBody{ entity, componentNode }); };
	parsers["Sprite"] = [](auto entity, const auto* componentNode) { entity.assign<SpriteComponent>(componentNode); };
	parsers["Label"] = [](auto entity, const auto* componentNode) { entity.assign<LabelComponent>(componentNode); };
	parsers["Particle"] = [](auto entity, const auto* componentNode) { entity.assign<ParticleComponent>(componentNode); };
	parsers["Health"] = [](auto entity, const auto* componentNode) { entity.assign<HealthComponent>(componentNode); };
	parsers["Damage"] = [](auto entity, const auto* componentNode) { entity.assign<DamageComponent>(componentNode); };
	parsers["Sound"] = [](auto entity, const auto* componentNode) { entity.assign<SoundComponent>(componentNode); };
	parsers["Animation"] = [](auto entity, const auto* componentNode) { entity.assign<AnimationComponent>(componentNode); };
	parsers["Weapon"] = [](auto entity, const auto* componentNode) { entity.assign<WeaponComponent>(componentNode); };
	parsers["Explosion"] = [](auto entity, const auto* componentNode) { entity.assign<ExplosionComponent>(componentNode); };
	parsers["Speed"] = [](auto entity, const auto* componentNode) { entity.assign<SpeedComponent>(componentNode); };
}

entityx::Entity EntityFactory::createEntity(const std::string& entityName)
{
	auto entity = entityManager.create();

	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(entityName + ".xml");
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* entityNode = doc.RootElement())
	{
		for (auto componentNode = entityNode->FirstChildElement(); componentNode; componentNode = componentNode->NextSiblingElement())
		{
			if (parsers.count(componentNode->Value()))
			{
				parsers[componentNode->Value()](entity, componentNode);
			}
		}
	}

	eventManager.emit(EntityCreated{ entity });

	return entity;
}