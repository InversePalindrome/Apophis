/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EntityFactory.cpp
InversePalindrome.com
*/


#include "Tags.hpp"
#include "Events.hpp"
#include "AIComponent.hpp"
#include "EntityFactory.hpp"
#include "BodyComponent.hpp"
#include "ItemComponent.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "SoundComponent.hpp"
#include "LabelComponent.hpp"
#include "AvoidComponent.hpp"
#include "FlockComponent.hpp"
#include "QueueComponent.hpp"
#include "SteerComponent.hpp"
#include "SpriteComponent.hpp"
#include "WeaponComponent.hpp"
#include "ArriveComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "PredictComponent.hpp"
#include "ImpulseComponent.hpp"
#include "PowerUpComponent.hpp"
#include "ParticleComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"

#include <cocos/platform/CCFileUtils.h>


EntityFactory::EntityFactory(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	entityManager(entityManager),
	eventManager(eventManager)
{
	parsers.emplace("Player", [](auto entity, const auto* componentNode) { entity.assign<Player>(); });
	parsers.emplace("Satellite", [](auto entity, const auto* componentNode) { entity.assign<Satellite>(); });
	parsers.emplace("Steer", [](auto entity, const auto* componentNode) { entity.assign<SteerComponent>(); });
	parsers.emplace("AI", [](auto entity, const auto* componentNode) { entity.assign<AIComponent>(componentNode); });
	parsers.emplace("Pursue", [](auto entity, const auto* componentNode) { entity.assign<PursueComponent>(componentNode); });
	parsers.emplace("Evade", [](auto entity, const auto* componentNode) { entity.assign<EvadeComponent>(componentNode); });
	parsers.emplace("Avoid", [](auto entity, const auto* componentNode) { entity.assign<AvoidComponent>(componentNode); });
	parsers.emplace("Arrive", [](auto entity, const auto* componentNode) { entity.assign<ArriveComponent>(componentNode); });
	parsers.emplace("Wander", [](auto entity, const auto* componentNode) { entity.assign<WanderComponent>(componentNode); });
	parsers.emplace("Patrol", [](auto entity, const auto* componentNode) { entity.assign<PatrolComponent>(componentNode); });
	parsers.emplace("Flock", [](auto entity, const auto* componentNode) { entity.assign<FlockComponent>(componentNode); });
	parsers.emplace("Follow", [](auto entity, const auto* componentNode) { entity.assign<FollowComponent>(componentNode); });
	parsers.emplace("Queue", [](auto entity, const auto* componentNode) { entity.assign<QueueComponent>(componentNode); });
	parsers.emplace("Body", [&eventManager](auto entity, const auto* componentNode) { eventManager.emit(CreateBody{ entity, componentNode }); });
	parsers.emplace("Sprite", [](auto entity, const auto* componentNode) { entity.assign<SpriteComponent>(componentNode); });
	parsers.emplace("Label", [](auto entity, const auto* componentNode) { entity.assign<LabelComponent>(componentNode); });
	parsers.emplace("Particle", [](auto entity, const auto* componentNode) { entity.assign<ParticleComponent>(componentNode); });
	parsers.emplace("Drop", [](auto entity, const auto* componentNode) { entity.assign<DropComponent>(componentNode); });
	parsers.emplace("Item", [](auto entity, const auto* componentNode) { entity.assign<ItemComponent>(componentNode); });
	parsers.emplace("Health", [](auto entity, const auto* componentNode) { entity.assign<HealthComponent>(componentNode); });
	parsers.emplace("Damage", [](auto entity, const auto* componentNode) { entity.assign<DamageComponent>(componentNode); });
	parsers.emplace("Vision", [](auto entity, const auto* componentNode) { entity.assign<VisionComponent>(componentNode); });
	parsers.emplace("Sound", [](auto entity, const auto* componentNode) { entity.assign<SoundComponent>(componentNode); });
	parsers.emplace("Animation", [](auto entity, const auto* componentNode) { entity.assign<AnimationComponent>(componentNode); });
	parsers.emplace("Weapon", [](auto entity, const auto* componentNode) { entity.assign<WeaponComponent>(componentNode); });
	parsers.emplace("Explosion", [](auto entity, const auto* componentNode) { entity.assign<ExplosionComponent>(componentNode); });
	parsers.emplace("Speed", [](auto entity, const auto* componentNode) { entity.assign<SpeedComponent>(componentNode); });
	parsers.emplace("Impulse", [](auto entity, const auto* componentNode) { entity.assign<ImpulseComponent>(componentNode); });
	parsers.emplace("PowerUp", [](auto entity, const auto* componentNode) { entity.assign<PowerUpComponent>(componentNode); });
}

entityx::Entity EntityFactory::createEntity(const std::string& filename) 
{
	auto entity = entityManager.create();
	
	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(filename + ".xml");
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* entityNode = doc.RootElement())
	{
		for (const auto* componentNode = entityNode->FirstChildElement(); componentNode; componentNode = componentNode->NextSiblingElement())
		{
			if (parsers.count(componentNode->Value()))
			{
				parsers.at(componentNode->Value())(entity, componentNode);
			}
		}
	}

	eventManager.emit(EntityParsed{ entity });

	return entity;
}

void EntityFactory::createEntities(const std::string& filename)
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
			auto entity = createEntity(entityNode->Value());
			
			const auto* x = entityNode->Attribute("x");
			const auto* y = entityNode->Attribute("y");

			if (x && y)
			{
				eventManager.emit(SetNodePosition{ entity, {std::stof(x) * PTM_RATIO, std::stof(y) * PTM_RATIO} });
				eventManager.emit(SetBodyPosition{ entity, {std::stof(x), std::stof(y)} });
			}

			if (const auto* angle = entityNode->Attribute("angle"))
			{
				eventManager.emit(SetNodeRotation{ entity, std::stof(angle) });
				eventManager.emit(SetBodyAngle{ entity, DegreesToRadians * std::stof(angle) });
			}
		}
	}
}