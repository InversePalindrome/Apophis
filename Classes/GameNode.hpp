/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameNode.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <cocos/2d/CCNode.h>

#include <Box2D/Common/b2Math.h>

#include <entityx/Event.h>
#include <entityx/Entity.h>
#include <entityx/System.h>


class GameNode : public cocos2d::Node, public entityx::Receiver<GameNode>
{
public:
    explicit GameNode(const std::string& level);

    virtual bool init() override;
    virtual void update(float dt) override;
    virtual void receive(const EntityDied& event);

    static GameNode* create(const std::string& level);

private:
    entityx::EventManager eventManager;
    entityx::EntityManager entityManager;
    entityx::SystemManager systemManager;

    std::string level;
    b2Vec2 mapDimensions;

    void initSystems();
    void reloadGame();
};