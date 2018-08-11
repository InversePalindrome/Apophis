/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Components.hpp
InversePalindrome.com
*/


#pragma once

#include <brigand/sequences/list.hpp>

#include "BodyComponent.hpp"
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


using Components = brigand::list<TransformComponent, ObjectComponent, BodyComponent, DistanceJointComponent, SpeedComponent, 
                               	 AccelerationComponent, SpriteComponent, LabelComponent, ParticleComponent,
                                 SoundComponent, HealthComponent, DamageComponent,  WeaponComponent, DropComponent, SpeedBoostComponent, 
                                 RegenBoostComponent, ExplosionComponent, VisionComponent, WanderComponent, PatrolComponent, 
	                             FollowComponent, PursueComponent, AvoidComponent, FlockComponent, QueueComponent, SatelliteComponent,
                                 PlayerComponent, StrikerComponent>;