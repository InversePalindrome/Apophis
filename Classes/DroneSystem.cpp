/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneSystem.cpp
InversePalindrome.com
*/


#include "DroneSystem.hpp"
#include "ObjectComponent.hpp"
#include "SteeringBehaviors.hpp"
#include "TransformComponent.hpp"


DroneSystem::DroneSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
    droneTree(beehive::Builder<DroneContext>()
        .selector()
        .sequence()
        .leaf([&entityManager](auto& context)
            {
                return (context.leaderBody->getPosition() - context.body.getPosition()).Length() <= context.vision.getVisionDistance();
            }
        ).void_leaf([&entityManager](auto& context)
            {
                auto directionVector = context.leaderBody->getLinearVelocity();
                directionVector.Normalize();
                directionVector *= context.follow.getDistanceFromLeader();

                const auto aheadPoint = context.leaderBody->getPosition() + directionVector;
                const auto behindPoint = context.leaderBody->getPosition() - directionVector;

                if (b2RayCastOutput rayOutput; context.body.raycast(rayOutput, { context.leaderBody->getPosition(), aheadPoint, 1.f }))
                {
                    context.body.applyLinearImpulse(SteeringBehaviors::evade(context.body.getPosition(), context.leaderBody->getPosition(), context.body.getLinearVelocity(), context.leaderBody->getLinearVelocity(), context.speed.getMaxLinearSpeed()));
                }

                context.body.applyLinearImpulse(SteeringBehaviors::arrive(context.body.getPosition(), behindPoint, context.body.getLinearVelocity(), context.arrive.getSlowRadius(), context.speed.getMaxLinearSpeed()));
                context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.body.getPosition() + context.body.getLinearVelocity(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));

                std::vector<b2Vec2> neighborPositions;

                entityManager.each<FlockComponent, BodyComponent>([&context, &neighborPositions](auto entity, const auto& flock, const auto& body)
                    {
                        if (context.drone != entity && context.flock.getGroupID() == flock.getGroupID() && (context.body.getPosition() - body.getPosition()).Length() <= context.flock.getGroupRadius())
                        {
                            neighborPositions.push_back(body.getPosition());
                        }
                    });

                context.body.applyLinearImpulse(SteeringBehaviors::separateForce(context.body.getPosition(), neighborPositions, context.flock.getSeparationForce()));
            })
                .end()
                .void_leaf([](auto& context)
                    {
                        context.body.applyLinearImpulse(SteeringBehaviors::wander(context.body.getPosition(), context.body.getLinearVelocity(), context.wander.getWanderDistance(), context.wander.getWanderRadius(), context.wander.getWanderRate(), context.wander.getWanderAngle(), context.speed.getMaxLinearSpeed()));
                        context.body.applyAngularImpulse(SteeringBehaviors::face(context.body.getPosition(), context.body.getPosition() + context.body.getLinearVelocity(), context.body.getAngle(), context.body.getAngularVelocity(), context.body.getInertia()));
                    }).end().build())
{
}

void DroneSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
    entityManager.each<ObjectComponent, BodyComponent, WanderComponent, SpeedComponent, ArriveComponent, FollowComponent, FlockComponent, VisionComponent>
        ([this, &entityManager](auto entity, const auto& object, auto& body, auto& wander, const auto& speed, const auto& arrive, const auto& follow, const auto& flock, const auto& vision)
            {
                if (object.getObjectType() == +ObjectType::Drone)
                {
                    if (auto leaderEntity = entityManager.get(entityManager.create_id(follow.getLeaderID())))
                    {
                        if (const auto leaderBody = leaderEntity.component<BodyComponent>())
                        {
                            droneTree.process(DroneContext{ entity, leaderEntity, body, wander, speed, arrive, follow, flock, vision, leaderBody });
                        }
                    }
                }
            });
}
