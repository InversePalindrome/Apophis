/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "MathUtility.hpp"
#include "EntityParser.hpp"
#include "BodyComponent.hpp"
#include "ItemComponent.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "LabelComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "ForceComponent.hpp"
#include "ObjectComponent.hpp"
#include "SpriteComponent.hpp"
#include "WeaponComponent.hpp"
#include "ArriveComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "PursueComponent.hpp"
#include "ImpulseComponent.hpp"
#include "PowerUpComponent.hpp"
#include "ParticleComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "AnchorPointComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


EntityParser::EntityParser(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	entityManager(entityManager),
	eventManager(eventManager)
{
	tagParsers.emplace("Player", [](auto entity) { entity.assign<Player>(); });
	tagParsers.emplace("Striker", [](auto entity) { entity.assign<Striker>(); });

	componentParsers.emplace("Object", [](auto entity, const auto* componentNode) { entity.assign<ObjectComponent>(componentNode); });
	componentParsers.emplace("Pursue", [](auto entity, const auto* componentNode) { entity.assign<PursueComponent>(componentNode); });
	componentParsers.emplace("Avoid", [](auto entity, const auto* componentNode) { entity.assign<AvoidComponent>(componentNode); });
	componentParsers.emplace("Arrive", [](auto entity, const auto* componentNode) { entity.assign<ArriveComponent>(componentNode); });
	componentParsers.emplace("Wander", [](auto entity, const auto* componentNode) { entity.assign<WanderComponent>(componentNode); });
	componentParsers.emplace("Patrol", [](auto entity, const auto* componentNode) { entity.assign<PatrolComponent>(componentNode); });
	componentParsers.emplace("Flock", [](auto entity, const auto* componentNode) { entity.assign<FlockComponent>(componentNode); });
	componentParsers.emplace("Follow", [](auto entity, const auto* componentNode) { entity.assign<FollowComponent>(componentNode); });
	componentParsers.emplace("Queue", [](auto entity, const auto* componentNode) { entity.assign<QueueComponent>(componentNode); });
	componentParsers.emplace("Body", [&eventManager](auto entity, const auto* componentNode) { eventManager.emit(CreateBody{ entity, componentNode }); });
	componentParsers.emplace("Sprite", [](auto entity, const auto* componentNode) { entity.assign<SpriteComponent>(componentNode); });
	componentParsers.emplace("Label", [](auto entity, const auto* componentNode) { entity.assign<LabelComponent>(componentNode); });
	componentParsers.emplace("Particle", [](auto entity, const auto* componentNode) { entity.assign<ParticleComponent>(componentNode); });
	componentParsers.emplace("Satellite", [](auto entity, const auto* componentNode) { entity.assign<SatelliteComponent>(componentNode); });
	componentParsers.emplace("Drop", [](auto entity, const auto* componentNode) { entity.assign<DropComponent>(componentNode); });
	componentParsers.emplace("Item", [](auto entity, const auto* componentNode) { entity.assign<ItemComponent>(componentNode); });
	componentParsers.emplace("Health", [](auto entity, const auto* componentNode) { entity.assign<HealthComponent>(componentNode); });
	componentParsers.emplace("Damage", [](auto entity, const auto* componentNode) { entity.assign<DamageComponent>(componentNode); });
	componentParsers.emplace("Vision", [](auto entity, const auto* componentNode) { entity.assign<VisionComponent>(componentNode); });
	componentParsers.emplace("Sound", [](auto entity, const auto* componentNode) { entity.assign<SoundComponent>(componentNode); });
	componentParsers.emplace("Animation", [](auto entity, const auto* componentNode) { entity.assign<AnimationComponent>(componentNode); });
	componentParsers.emplace("Weapon", [](auto entity, const auto* componentNode) { entity.assign<WeaponComponent>(componentNode); });
	componentParsers.emplace("Explosion", [](auto entity, const auto* componentNode) { entity.assign<ExplosionComponent>(componentNode); });
	componentParsers.emplace("Speed", [](auto entity, const auto* componentNode) { entity.assign<SpeedComponent>(componentNode); });
	componentParsers.emplace("Impulse", [](auto entity, const auto* componentNode) { entity.assign<ImpulseComponent>(componentNode); });
	componentParsers.emplace("Force", [](auto entity, const auto* componentNode) {entity.assign<ForceComponent>(componentNode); });
	componentParsers.emplace("AnchorPoint", [](auto entity, const auto* componentNode) { entity.assign<AnchorPointComponent>(componentNode); });
	componentParsers.emplace("PowerUp", [](auto entity, const auto* componentNode) { entity.assign<PowerUpComponent>(componentNode); });
}

entityx::Entity EntityParser::createEntity(const std::string& filename)
{
	auto entity = entityManager.create();

	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(filename + ".xml");
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* entityNode = doc.RootElement())
	{
		if (const auto* tagsNode = entityNode->FirstChildElement("Tags"))
		{
			for (const auto* tagNode = tagsNode->FirstChildElement(); tagNode; tagNode = tagNode->NextSiblingElement())
			{
				if (tagParsers.count(tagNode->Value()))
				{
					tagParsers.at(tagNode->Value())(entity);
				}
			}
		}
		if (const auto* componentsNode = entityNode->FirstChildElement("Components"))
		{
			for (const auto* componentNode = componentsNode->FirstChildElement(); componentNode; componentNode = componentNode->NextSiblingElement())
			{
				if (componentParsers.count(componentNode->Value()))
				{
					componentParsers.at(componentNode->Value())(entity, componentNode);
				}
			}
		}
	}

	eventManager.emit(EntityParsed{ entity });

	return entity;
}

void EntityParser::createEntities(const std::string& filename)
{
	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(filename + ".xml");
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* entitiesNode = doc.RootElement())
	{
		for (const auto* entityNode = entitiesNode->FirstChildElement(); entityNode; entityNode = entityNode->NextSiblingElement())
		{
			createEntity(entityNode->Value());
		}
	}
}