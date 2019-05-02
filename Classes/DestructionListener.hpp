/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DestructionListener.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Joints/b2Joint.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

#include <entityx/Entity.h>


class DestructionListener : public b2DestructionListener
{
public:
    explicit DestructionListener(entityx::EntityManager& entityManager);

private:
    entityx::EntityManager& entityManager;

    virtual void SayGoodbye(b2Joint* joint) override;
    virtual void SayGoodbye(b2Fixture* fixture) override;
};