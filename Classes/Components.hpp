/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ComponentList.hpp
InversePalindrome.com
*/


#pragma once

#include "NameComponent.hpp"
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
#include "TargetComponent.hpp"
#include "VisionComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "HealthComponent.hpp"
#include "DamageComponent.hpp"
#include "SpriteComponent.hpp"
#include "ArriveComponent.hpp"
#include "PathwayComponent.hpp"
#include "ParticleComponent.hpp"
#include "AddComponentHandle.hpp"
#include "TransformComponent.hpp"
#include "AnimationComponent.hpp"
#include "ExplosionComponent.hpp"
#include "SatelliteComponent.hpp"
#include "SpeedBoostComponent.hpp"
#include "RegenBoostComponent.hpp"
#include "AccelerationComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <brigand/sequences/list.hpp>
#include <brigand/adapted/variant.hpp>
#include <brigand/algorithms/transform.hpp>


using ComponentList = brigand::list<NameComponent, TransformComponent, ObjectComponent, BodyComponent, DistanceJointComponent, SpeedComponent,
    AccelerationComponent, SpriteComponent, ArriveComponent, LabelComponent, ParticleComponent, AnimationComponent,
    SoundComponent, HealthComponent, DamageComponent, WeaponComponent, TargetComponent, DropComponent, SpeedBoostComponent,
    RegenBoostComponent, ExplosionComponent, VisionComponent, WanderComponent, PatrolComponent, PathwayComponent,
    FollowComponent, AvoidComponent, FlockComponent, QueueComponent, SatelliteComponent, StateComponent>;

using ComponentHandleList = brigand::transform<ComponentList, AddComponetHandle<brigand::_1>>;

using ComponentHandleVariant = brigand::as_variant<ComponentHandleList>;