/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.cpp
InversePalindrome.com
*/


#include "Events.hpp"
#include "StrikerSystem.hpp"
#include "ObjectComponent.hpp"
#include "TargetComponent.hpp"
#include "SteeringBehaviors.hpp"


StrikerSystem::StrikerSystem(entityx::EventManager& eventManager) :
    strikerTree(beehive::Builder<StrikerContext>()
        .selector()
        .sequence()
        .leaf([this](auto& context)
            {
                return (context.targetTransform->getPosition() - context.body.getPosition()).Length() <= context.vision.getVisionDistance();
            })
        .selector()
                .sequence()
                .leaf([](auto& context)
                    {
                        const auto healthBreakPercent = 0.2f;

                        return context.health.getCurrentHitpoints() >= context.health.getMaxHitpoints() * healthBreakPercent;
                    })
                .void_leaf([this, &eventManager](auto& context)
                    {
                        context.body.applyLinearImpulse(SteeringBehaviors::seek(context.body.getPosition(), context.targetTransform->getPosition(), context.body.getLinearVelocity(), context.speed.getMaxLinearSpeed()));
                        context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.targetTransform->getPosition(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));

                        eventManager.emit(ShootProjectile{ context.striker });
                    })
                        .end()
                        .void_leaf([this](auto& context)
                            {
                                context.body.applyLinearImpulse(SteeringBehaviors::seek(context.body.getPosition(), context.targetTransform->getPosition(), context.body.getLinearVelocity(), -context.speed.getMaxLinearSpeed()));
                                context.body.applyAngularImpulse(SteeringBehaviors::face(context.targetTransform->getPosition(), context.body.getPosition(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
                            }).end().end()
                                .void_leaf([](auto& context)
                                    {
                                        context.body.applyLinearImpulse(SteeringBehaviors::wander(context.body.getPosition(), context.body.getLinearVelocity(), context.wander.getWanderDistance(), context.wander.getWanderRadius(), context.wander.getWanderRate(), context.wander.getWanderAngle(), context.speed.getMaxLinearSpeed()));
                                        context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.body.getPosition() + context.body.getLinearVelocity(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
                                    }).end().build())
{
}

                                    void StrikerSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
                                    {
                                        entityManager.each<ObjectComponent, TargetComponent, BodyComponent, SpeedComponent, WanderComponent, VisionComponent, HealthComponent>
                                            ([this, &entityManager](auto entity, const auto & object, const auto & target, auto & body, const auto & speed, auto & wander, const auto & vision, const auto & health)
                                                {
                                                    if (object.getObjectType() == +ObjectType::Striker)
                                                    {
                                                        if (auto targetEntity = entityManager.get(entityManager.create_id(target.getTargetID())))
                                                        {
                                                            if (const auto targetTransform = targetEntity.component<TransformComponent>())
                                                            {
                                                                strikerTree.process(StrikerContext{ entity, targetEntity, body, speed, wander, vision, health, targetTransform });
                                                            }
                                                        }
                                                    }
                                                });
                                    }