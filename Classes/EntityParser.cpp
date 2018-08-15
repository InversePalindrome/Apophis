/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityParser.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "EntityParser.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "LabelComponent.hpp"
#include "ObjectComponent.hpp"
#include "PlayerComponent.hpp"
#include "WeaponComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "PursueComponent.hpp"
#include "SpriteComponent.hpp"
#include "StrikerComponent.hpp"
#include "ParticleComponent.hpp"
#include "TransformComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"
#include "AccelerationComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


const std::unordered_map<std::string, std::function<void(entityx::Entity&, entityx::EventManager&, const pugi::xml_node&)>> EntityParser::componentParsers
{
	{ "Sprite", [](auto entity, auto&, const auto& componentNode) { entity.assign<SpriteComponent>(componentNode); } },
    { "Label", [](auto entity, auto&, const auto& componentNode) { entity.assign<LabelComponent>(componentNode); } },
    { "Particle", [](auto entity, auto&, const auto& componentNode) { entity.assign<ParticleComponent>(componentNode); } },
    { "Body", [](auto entity, auto& eventManager, const auto& componentNode) { eventManager.emit(CreateBody{ entity, componentNode }); } },
    { "DistanceJoint", [](auto entity, auto& eventManager, const auto& componentNode) { eventManager.emit(CreateJoint<DistanceJointComponent>{ entity, componentNode }); } },
    { "Transform", [](auto entity, auto&, const auto& componentNode) { entity.assign<TransformComponent>(componentNode); } },
    { "Object", [](auto entity, auto&, const auto& componentNode) { entity.assign<ObjectComponent>(componentNode); } },
    { "Pursue", [](auto entity,  auto&, const auto& componentNode) { entity.assign<PursueComponent>(componentNode); } },
    { "Avoid", [](auto entity, auto&, const auto& componentNode) { entity.assign<AvoidComponent>(componentNode); } },
    { "Wander", [](auto entity, auto&, const auto& componentNode) { entity.assign<WanderComponent>(componentNode); } },
    { "Patrol", [](auto entity, auto&, const auto& componentNode) { entity.assign<PatrolComponent>(componentNode); } },
    { "Flock", [](auto entity, auto&, const auto& componentNode) { entity.assign<FlockComponent>(componentNode); } },
    { "Follow", [](auto entity, auto&, const auto& componentNode) { entity.assign<FollowComponent>(componentNode); } },
    { "Queue", [](auto entity, auto&, const auto& componentNode) { entity.assign<QueueComponent>(componentNode); } },
    { "Satellite", [](auto entity, auto&, const auto& componentNode) { entity.assign<SatelliteComponent>(componentNode); } },
    { "Drop", [](auto entity, auto&, const auto& componentNode) { entity.assign<DropComponent>(componentNode); } },
    { "Health", [](auto entity, auto&, const auto& componentNode) { entity.assign<HealthComponent>(componentNode); } },
    { "Damage", [](auto entity, auto&, const auto& componentNode) { entity.assign<DamageComponent>(componentNode); } },
    { "Vision", [](auto entity, auto&, const auto& componentNode) { entity.assign<VisionComponent>(componentNode); } },
    { "Sound", [](auto entity, auto&, const auto& componentNode) { entity.assign<SoundComponent>(componentNode); } },
    { "Weapon", [](auto entity, auto&, const auto& componentNode) { entity.assign<WeaponComponent>(componentNode); } },
    { "Explosion", [](auto entity, auto&, const auto& componentNode) { entity.assign<ExplosionComponent>(componentNode); } },
    { "Speed", [](auto entity, auto&, const auto& componentNode) { entity.assign<SpeedComponent>(componentNode); } },
    { "Acceleration", [](auto entity, auto&, const auto& componentNode) { entity.assign<AccelerationComponent>(componentNode); } },
    { "SpeedBoost", [](auto entity, auto&, const auto& componentNode) { entity.assign<SpeedBoostComponent>(componentNode); } },
    { "RegenBoost", [](auto entity, auto&, const auto& componentNode) { entity.assign<RegenBoostComponent>(componentNode); } },
    { "Player", [](auto entity, auto&, const auto&) {entity.assign<PlayerComponent>(); } },
    { "Striker", [](auto entity, auto&, const auto&) { entity.assign<StrikerComponent>(); } }
};

void EntityParser::parseEntity(entityx::Entity entity, entityx::EventManager& eventManager, const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
	{
		if (const auto entityNode = doc.child("Entity"))
		{
			parseEntity(entity, eventManager, entityNode);
		}
	}
}

void EntityParser::parseEntity(entityx::Entity entity, entityx::EventManager& eventManager, const pugi::xml_node& entityNode)
{
	for (const auto componentNode : entityNode.children())
	{
		if (componentParsers.count(componentNode.name()))
		{
			componentParsers.at(componentNode.name())(entity, eventManager, componentNode);
		}
	}

	eventManager.emit(EntityParsed{ entity });
}