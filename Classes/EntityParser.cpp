/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "EntityParser.hpp"
#include "BodyComponent.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "ObjectComponent.hpp"
#include "WeaponComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "PursueComponent.hpp"
#include "GeometryComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "SceneNodeComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"
#include "AnchorPointComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


EntityParser::EntityParser(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	entityManager(entityManager),
	eventManager(eventManager)
{
	componentParsers.emplace("SceneNode", [](auto entity, const auto& componentNode) { entity.assign<SceneNodeComponent>(componentNode); });
	componentParsers.emplace("Geometry", [](auto entity, const auto& componentNode) { entity.assign<GeometryComponent>(componentNode); });
	componentParsers.emplace("Object", [](auto entity, const auto& componentNode) { entity.assign<ObjectComponent>(componentNode); });
	componentParsers.emplace("Pursue", [](auto entity, const auto& componentNode) { entity.assign<PursueComponent>(componentNode); });
	componentParsers.emplace("Avoid", [](auto entity, const auto& componentNode) { entity.assign<AvoidComponent>(componentNode); });
	componentParsers.emplace("Wander", [](auto entity, const auto& componentNode) { entity.assign<WanderComponent>(componentNode); });
	componentParsers.emplace("Patrol", [](auto entity, const auto& componentNode) { entity.assign<PatrolComponent>(componentNode); });
	componentParsers.emplace("Flock", [](auto entity, const auto& componentNode) { entity.assign<FlockComponent>(componentNode); });
	componentParsers.emplace("Follow", [](auto entity, const auto& componentNode) { entity.assign<FollowComponent>(componentNode); });
	componentParsers.emplace("Queue", [](auto entity, const auto& componentNode) { entity.assign<QueueComponent>(componentNode); });
	componentParsers.emplace("Body", [](auto entity, const auto& componentNode) { entity.assign<BodyComponent>(componentNode); });
	componentParsers.emplace("Satellite", [](auto entity, const auto& componentNode) { entity.assign<SatelliteComponent>(componentNode); });
	componentParsers.emplace("Drop", [](auto entity, const auto& componentNode) { entity.assign<DropComponent>(componentNode); });
	componentParsers.emplace("Health", [](auto entity, const auto& componentNode) { entity.assign<HealthComponent>(componentNode); });
	componentParsers.emplace("Damage", [](auto entity, const auto& componentNode) { entity.assign<DamageComponent>(componentNode); });
	componentParsers.emplace("Vision", [](auto entity, const auto& componentNode) { entity.assign<VisionComponent>(componentNode); });
	componentParsers.emplace("Sound", [](auto entity, const auto& componentNode) { entity.assign<SoundComponent>(componentNode); });
	componentParsers.emplace("Animation", [](auto entity, const auto& componentNode) { entity.assign<AnimationComponent>(componentNode); });
	componentParsers.emplace("Weapon", [](auto entity, const auto& componentNode) { entity.assign<WeaponComponent>(componentNode); });
	componentParsers.emplace("Explosion", [](auto entity, const auto& componentNode) { entity.assign<ExplosionComponent>(componentNode); });
	componentParsers.emplace("Speed", [](auto entity, const auto& componentNode) { entity.assign<SpeedComponent>(componentNode); });
	componentParsers.emplace("AnchorPoint", [](auto entity, const auto& componentNode) { entity.assign<AnchorPointComponent>(componentNode); });
	componentParsers.emplace("SpeedBoost", [](auto entity, const auto& componentNode) { entity.assign<SpeedBoostComponent>(componentNode); });
	componentParsers.emplace("RegenBoost", [](auto entity, const auto& componentNode) { entity.assign<RegenBoostComponent>(componentNode); });

	tagParsers.emplace("Player", [](auto entity) { entity.assign<Player>(); });
	tagParsers.emplace("Striker", [](auto entity) { entity.assign<Striker>(); });
}

entityx::Entity EntityParser::createEntity(const std::string& filename)
{
	auto entity = entityManager.create();

	pugi::xml_document doc;
	
	if (doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename + ".xml").c_str()))
	{
		if (const auto entityNode = doc.child("Entity"))
		{
			for (const auto componentsNode : entityNode.children("Components"))
			{
				for (const auto componentNode : componentsNode.children())
				{
					if (componentParsers.count(componentNode.name()))
					{
						componentParsers.at(componentNode.name())(entity, componentNode);
					}    
				}
			}

			for (const auto tagsNode : entityNode.children("Tags"))
			{
				for (const auto tagNode : tagsNode.children())
				{
					if (tagParsers.count(tagNode.name()))
					{
						tagParsers.at(tagNode.name())(entity);
					}
				}
			}
		}
	}

	eventManager.emit(EntityParsed{ entity });

	return entity;
}