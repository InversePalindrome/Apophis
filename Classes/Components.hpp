/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Components.hpp
InversePalindrome.com
*/


#pragma once

#include "TagsComponent.hpp"
#include "BodyComponent.hpp"
#include "DropComponent.hpp"
#include "StateComponent.hpp"
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
#include "ArriveComponent.hpp"
#include "ParticleComponent.hpp"
#include "TransformComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"
#include "AccelerationComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <entityx/Entity.h>

#include <brigand/sequences/list.hpp>

#include <variant>


using Components = brigand::list<TransformComponent, ObjectComponent, TagsComponent, BodyComponent, DistanceJointComponent, SpeedComponent, 
                               	 AccelerationComponent, SpriteComponent, ArriveComponent, LabelComponent, ParticleComponent, AnimationComponent,
                                 SoundComponent, HealthComponent, DamageComponent,  WeaponComponent, DropComponent, SpeedBoostComponent, 
                                 RegenBoostComponent, ExplosionComponent, VisionComponent, WanderComponent, PatrolComponent, 
	                             FollowComponent, PursueComponent, AvoidComponent, FlockComponent, QueueComponent, SatelliteComponent, StateComponent>;

using ComponentsVariant = std::variant<entityx::ComponentHandle<TransformComponent>, entityx::ComponentHandle<ObjectComponent>, entityx::ComponentHandle<TagsComponent>,
	                                   entityx::ComponentHandle<BodyComponent>, entityx::ComponentHandle<SpeedComponent>, entityx::ComponentHandle<DistanceJointComponent>,
	                                   entityx::ComponentHandle<AccelerationComponent>, entityx::ComponentHandle<SpriteComponent>, entityx::ComponentHandle<ArriveComponent>, entityx::ComponentHandle<LabelComponent>,
	                                   entityx::ComponentHandle<ParticleComponent>, entityx::ComponentHandle<AnimationComponent>, entityx::ComponentHandle<SoundComponent>, entityx::ComponentHandle<HealthComponent>,
	                                   entityx::ComponentHandle<DamageComponent>, entityx::ComponentHandle<WeaponComponent>, entityx::ComponentHandle<DropComponent>,
	                                   entityx::ComponentHandle<SpeedBoostComponent>, entityx::ComponentHandle<RegenBoostComponent>, entityx::ComponentHandle<ExplosionComponent>,
	                                   entityx::ComponentHandle<VisionComponent>, entityx::ComponentHandle<WanderComponent>, entityx::ComponentHandle<PatrolComponent>,
	                                   entityx::ComponentHandle<FollowComponent>, entityx::ComponentHandle<PursueComponent>, entityx::ComponentHandle<AvoidComponent>,
	                                   entityx::ComponentHandle<FlockComponent>, entityx::ComponentHandle<QueueComponent>, entityx::ComponentHandle<SatelliteComponent>,
	                                   entityx::ComponentHandle<StateComponent>>;