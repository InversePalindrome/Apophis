/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DestructionListener.cpp
InversePalindrome.com
*/


#include "Joints.hpp"
#include "DestructionListener.hpp"

#include <brigand/algorithms/for_each.hpp>


DestructionListener::DestructionListener(entityx::EntityManager& entityManager) :
    entityManager(entityManager)
{
}

void DestructionListener::SayGoodbye(b2Joint* joint)
{
    brigand::for_each<Joints>([this, joint](auto jointElement) mutable
        {
            entityx::ComponentHandle<decltype(jointElement)::type> jointComponent;

            for (auto entity : entityManager.entities_with_components(jointComponent))
            {
                if (jointComponent->getJoint() == joint)
                {
                    jointComponent.remove();
                }
            }
        });
}

void DestructionListener::SayGoodbye(b2Fixture* fixture)
{

}