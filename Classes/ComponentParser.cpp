/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ComponentParser.cpp
InversePalindrome.com
*/


#include "ComponentParser.hpp"


const std::unordered_map<std::string, std::function<ComponentsVariant(entityx::Entity&)>> componentParser
{
	{ "Sprite", [](auto& entity)  { return entity.assign<SpriteComponent>(); } },
    { "Label", [](auto& entity) { return entity.assign<LabelComponent>(); } },
    { "Particle", [](auto& entity) { return entity.assign<ParticleComponent>(); } },
    { "Sound", [](auto& entity) { return entity.assign<SoundComponent>(); } },
    { "Animation", [](auto& entity) { return entity.assign<AnimationComponent>(); } },
	{ "Body", [](auto& entity) { return entity.assign<BodyComponent>(); } },
    { "Transform", [](auto& entity) { return entity.assign<TransformComponent>(); } },
    { "Object", [](auto& entity) { return entity.assign<ObjectComponent>(); } },
	{ "Tags", [](auto& entity) { return entity.assign<TagsComponent>(); }},
    { "State", [](auto& entity) { return entity.assign<StateComponent>(); } },
    { "Pursue", [](auto& entity) { return entity.assign<PursueComponent>(); } },
    { "Avoid", [](auto& entity) { return entity.assign<AvoidComponent>(); } },
    { "Wander", [](auto& entity) { return entity.assign<WanderComponent>(); } },
    { "Patrol", [](auto& entity) { return entity.assign<PatrolComponent>(); } },
    { "Flock", [](auto& entity) { return entity.assign<FlockComponent>(); } },
    { "Follow", [](auto& entity) { return entity.assign<FollowComponent>(); } },
    { "Queue", [](auto& entity) { return entity.assign<QueueComponent>(); } },
    { "Satellite", [](auto& entity) { return entity.assign<SatelliteComponent>(); } },
    { "Drop", [](auto& entity) { return entity.assign<DropComponent>(); } },
    { "Health", [](auto& entity) { return entity.assign<HealthComponent>(); } },
    { "Damage", [](auto& entity) { return entity.assign<DamageComponent>(); } },
    { "Vision", [](auto& entity) { return entity.assign<VisionComponent>(); } },
    { "Weapon", [](auto& entity) { return entity.assign<WeaponComponent>(); } },
    { "Explosion", [](auto& entity) { return entity.assign<ExplosionComponent>(); } },
    { "Speed", [](auto& entity) { return entity.assign<SpeedComponent>(); } },
    { "Acceleration", [](auto& entity) { return entity.assign<AccelerationComponent>(); } },
    { "SpeedBoost", [](auto& entity) { return entity.assign<SpeedBoostComponent>(); } },
    { "RegenBoost", [](auto& entity) { return entity.assign<RegenBoostComponent>(); } }
};