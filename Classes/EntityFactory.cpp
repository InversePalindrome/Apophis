/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityFactory.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "EntityFactory.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "LabelComponent.hpp"
#include "ObjectComponent.hpp"
#include "WeaponComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "PursueComponent.hpp"
#include "SpriteComponent.hpp"
#include "ParticleComponent.hpp"
#include "TransformComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"
#include "AccelerationComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


EntityFactory::EntityFactory(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	entityManager(entityManager),
	eventManager(eventManager),
	componentParsers{ 
		               { "Sprite", [](auto entity, const auto& componentNode) { entity.assign<SpriteComponent>(componentNode); } },
	                   { "Label", [](auto entity, const auto& componentNode) { entity.assign<LabelComponent>(componentNode); } },
		               { "Particle", [](auto entity, const auto& componentNode) { entity.assign<ParticleComponent>(componentNode); } },
                       { "Body", [&eventManager](auto entity, const auto& componentNode) { eventManager.emit(CreateBody{ entity, componentNode }); }},
               		   { "DistanceJoint", [&eventManager](auto entity, const auto& componentNode) { eventManager.emit(CreateDistanceJoint{ entity, componentNode }); } },
                	   { "Transform", [](auto entity, const auto& componentNode) { entity.assign<TransformComponent>(componentNode); } },
                       { "Object", [](auto entity, const auto& componentNode) { entity.assign<ObjectComponent>(componentNode); }},
                       { "Pursue", [](auto entity, const auto& componentNode) { entity.assign<PursueComponent>(componentNode); }},
                       { "Avoid", [](auto entity, const auto& componentNode) { entity.assign<AvoidComponent>(componentNode); }},
		               { "Wander", [](auto entity, const auto& componentNode) { entity.assign<WanderComponent>(componentNode); } },
	                   { "Patrol", [](auto entity, const auto& componentNode) { entity.assign<PatrolComponent>(componentNode); } },
		               { "Flock", [](auto entity, const auto& componentNode) { entity.assign<FlockComponent>(componentNode); } },
		               { "Follow", [](auto entity, const auto& componentNode) { entity.assign<FollowComponent>(componentNode); } },
                       { "Queue", [](auto entity, const auto& componentNode) { entity.assign<QueueComponent>(componentNode); }},
                       { "Satellite", [](auto entity, const auto& componentNode) { entity.assign<SatelliteComponent>(componentNode); }},
	                   { "Drop", [](auto entity, const auto& componentNode) { entity.assign<DropComponent>(componentNode); } },
                       { "Health", [](auto entity, const auto& componentNode) { entity.assign<HealthComponent>(componentNode); }},
                       { "Damage", [](auto entity, const auto& componentNode) { entity.assign<DamageComponent>(componentNode); }},
                       { "Vision", [](auto entity, const auto& componentNode) { entity.assign<VisionComponent>(componentNode); }},
		               { "Sound", [](auto entity, const auto& componentNode) { entity.assign<SoundComponent>(componentNode); } },
	                   { "Animation", [](auto entity, const auto& componentNode) { entity.assign<AnimationComponent>(componentNode); } },
                       { "Weapon", [](auto entity, const auto& componentNode) { entity.assign<WeaponComponent>(componentNode); }},
	                   { "Explosion", [](auto entity, const auto& componentNode) { entity.assign<ExplosionComponent>(componentNode); } },
                       { "Speed", [](auto entity, const auto& componentNode) { entity.assign<SpeedComponent>(componentNode); }},
                       { "Acceleration", [](auto entity, const auto& componentNode) { entity.assign<AccelerationComponent>(componentNode); }},
	                   { "SpeedBoost", [](auto entity, const auto& componentNode) { entity.assign<SpeedBoostComponent>(componentNode); } },
                       { "RegenBoost", [](auto entity, const auto& componentNode) { entity.assign<RegenBoostComponent>(componentNode); }} 
                   },
	tagParsers{ 
		         { "Player", [](auto entity) { entity.assign<Player>(); } },
			     { "Striker", [](auto entity) { entity.assign<Striker>(); } } 
              }
{
}

entityx::Entity EntityFactory::createEntity(const std::string& filename)
{
	auto entity = entityManager.create();

	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename + ".xml").c_str()))
	{
		if (const auto entityNode = doc.child("Entity"))
		{
			parseEntity(entity, entityNode);
		}
	}

	return entity;
}

entityx::Entity EntityFactory::createEntity(const pugi::xml_node& entityNode)
{
	auto entity = entityManager.create();

	parseEntity(entity, entityNode);

	return entity;
}

void EntityFactory::createEntities(const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename + ".xml").c_str()))
	{
		if (const auto entitiesNode = doc.child("Entities"))
		{
			for (const auto entityNode : entitiesNode.children("Entity"))
			{
				createEntity(entityNode);
			}
		}
	}
}

void EntityFactory::parseEntity(entityx::Entity& entity, const pugi::xml_node& entityNode)
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

	eventManager.emit(EntityParsed{ entity });
}