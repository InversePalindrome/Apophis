/*
Copyright (c) 2018 Inverse Palindrome
Apophis - JointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/Joints/b2Joint.h>

#include <pugixml.hpp>


class JointComponent
{
public:
    JointComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    b2Joint* getJoint();
    b2Joint* getJoint() const;
    void setJoint(b2Joint* joint);

    b2Body* getBodyA();
    b2Body* getBodyB();

    int getEntityIDA() const;
    void setEntityIDA(int entityIDA);

    int getEntityIDB() const;
    void setEntityIDB(int entityIDB);

    b2Vec2 getLocalAnchorA() const;
    void setLocalAnchorA(const b2Vec2& localAnchorA);

    b2Vec2 getLocalAnchorB() const;
    void setLocalAnchorB(const b2Vec2& localAnchorB);

private:
    b2Joint* joint;
    int entityIDA;
    int entityIDB;
    b2Vec2 localAnchorA;
    b2Vec2 localAnchorB;
};