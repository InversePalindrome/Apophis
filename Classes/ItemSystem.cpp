/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ItemSystem.cpp
InversePalindrome.com
*/


#include "ItemSystem.hpp"
#include "Conversions.hpp"
#include "EntityParser.hpp"
#include "DropComponent.hpp"
#include "SpeedComponent.hpp"
#include "HealthComponent.hpp"
#include "TransformComponent.hpp"


ItemSystem::ItemSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
    entityManager(entityManager),
    eventManager(eventManager),
    randomEngine(std::random_device()())
{
}

void ItemSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
    eventManager.subscribe<PickedUpItem>(*this);
}

void ItemSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void ItemSystem::receive(const entityx::EntityDestroyedEvent& event)
{
    const auto destroyedEntity = event.entity;

    if (const auto [destroyedDrop, destroyedTransform] = destroyedEntity.components<DropComponent, TransformComponent>(); destroyedDrop && destroyedTransform)
    {
        if (const auto& destroyedItemFilenames = destroyedDrop->getItemFilenames(); !destroyedItemFilenames.empty())
        {
            const auto& destroyedWeights = destroyedDrop->getWeights();

            std::discrete_distribution<> discreteDistribution(std::cbegin(destroyedWeights), std::cend(destroyedWeights));

            auto itemEntity = entityManager.create();

            EntityParser::parseEntity(itemEntity, eventManager, destroyedItemFilenames.at(discreteDistribution(randomEngine)));

            if (auto itemTransform = itemEntity.component<TransformComponent>())
            {
                itemTransform->setPosition(destroyedTransform->getPosition());

                eventManager.emit(UpdateTransform{ itemEntity });
            }
        }
    }
}

void ItemSystem::receive(const PickedUpItem& event)
{
    if (auto weapon = event.itemEntity.component<WeaponComponent>())
    {
        addWeapon(event.entity, weapon);
    }
    if (const auto regenBoost = event.itemEntity.component<RegenBoostComponent>())
    {
        addRegenBoost(event.entity, regenBoost);
    }
    if (const auto speedBoost = event.itemEntity.component<SpeedBoostComponent>())
    {
        addSpeedBoost(event.entity, speedBoost);
    }

    event.itemEntity.destroy();
}

void ItemSystem::addWeapon(entityx::Entity entity, entityx::ComponentHandle<WeaponComponent> weapon)
{
    entity.replace<WeaponComponent>(*weapon.get());
}

void ItemSystem::addRegenBoost(entityx::Entity entity, const entityx::ComponentHandle<RegenBoostComponent> regenBoost)
{
    if (auto entityHealth = entity.component<HealthComponent>())
    {
        const auto hitpointBoost = regenBoost->getHitpointBoost();

        const auto regenPeriodicTimerID = timer.add(std::chrono::milliseconds::zero(), [entityHealth, hitpointBoost](auto id) mutable
            {
                if (entityHealth)
                {
                    const auto regenHealth = entityHealth->getCurrentHitpoints() + hitpointBoost;

                    if (regenHealth <= entityHealth->getMaxHitpoints())
                    {
                        entityHealth->setCurrentHitpoints(regenHealth);
                    }
                }
            }, regenBoost->getRegenRate());

        timer.add(regenBoost->getRegenDuration(), [this, regenPeriodicTimerID](auto) { timer.remove(regenPeriodicTimerID); });
    }
}

void ItemSystem::addSpeedBoost(entityx::Entity entity, const entityx::ComponentHandle<SpeedBoostComponent> speedBoost)
{
    if (auto entitySpeed = entity.component<SpeedComponent>())
    {
        const auto originalSpeed = entitySpeed->getMaxLinearSpeed();

        entitySpeed->setMaxLinearSpeed(entitySpeed->getMaxLinearSpeed() * speedBoost->getSpeedBoostRatio());

        timer.add(speedBoost->getSpeedBoostDuration(), [entitySpeed, originalSpeed](auto) mutable
            {
                if (entitySpeed)
                {
                    entitySpeed->setMaxLinearSpeed(originalSpeed);
                }
            });
    }
}