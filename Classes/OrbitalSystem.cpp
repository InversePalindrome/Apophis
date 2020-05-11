/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "OrbitalSystem.hpp"
#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "SteeringBehaviors.hpp"
#include "SatelliteComponent.hpp"


void OrbitalSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
    entityManager.each<BodyComponent, SatelliteComponent, SpeedComponent>([&entityManager](auto entity, auto& body, const auto& satellite, const auto& speed)
        {
            if (auto primaryEntity = entityManager.get(entityManager.create_id(satellite.getPrimaryID())))
            {
                if (auto primaryBody = primaryEntity.component<BodyComponent>())
                {
                    body.applyLinearImpulse(SteeringBehaviors::orbit(body.getPosition(), primaryBody->getPosition(), body.getLinearVelocity(), satellite.getOrbitDirection() * speed.getMaxLinearSpeed()));
                    body.applyAngularImpulse(body.getInertia() * (satellite.getOrbitDirection() * speed.getMaxAngularSpeed() - body.getAngularVelocity()) / Constants::FPS);
                }
            }
        });
}