/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolSystem.cpp
InversePalindrome.com
*/


#include "PatrolSystem.hpp"
#include "PatrolComponent.hpp"
#include "ObjectComponent.hpp"
#include "PathwayComponent.hpp"
#include "SteeringBehaviors.hpp"


PatrolSystem::PatrolSystem() :
    patrolTree(beehive::Builder<PatrolContext>()
        .void_leaf([](auto& context)
            {
                context.body.applyLinearImpulse(SteeringBehaviors::seek(context.body.getPosition(), context.targetPoint, context.body.getLinearVelocity(), context.speed.getMaxLinearSpeed()));
            }).build())
{
}

void PatrolSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<CrossedWaypoint>(*this);
}

void PatrolSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
    entityManager.each<ObjectComponent, BodyComponent, SpeedComponent, PatrolComponent>
        ([this, &entityManager](auto entity, const auto & object, auto & body, const auto & speed, const auto & patrol)
            {
                if (auto pathEntity = entityManager.get(entityManager.create_id(patrol.getPathwayID())); pathEntity && object.getObjectType() == +ObjectType::Patrol)
                {
                    if (auto pathway = pathEntity.component<PathwayComponent>())
                    {
                        patrolTree.process(PatrolContext{ entity, pathway->operator[](patrol.getCurrentPointIndex()), body, speed });
                    }
                }
            });
}

void PatrolSystem::receive(const CrossedWaypoint& event)
{
    auto pathway = event.pathEntity.component<PathwayComponent>();
    auto patrol = event.patrolEntity.component<PatrolComponent>();

    if (pathway && patrol && patrol->getPathwayID() == event.pathEntity.id().index())
    {
        auto currentPointIndex = patrol->getCurrentPointIndex();

        if (++currentPointIndex == pathway->getPathwayPointsCount())
        {
            currentPointIndex = 0;
        }

        patrol->setCurrentPointIndex(currentPointIndex);
    }
}
