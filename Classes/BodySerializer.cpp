/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodySerializer.cpp
InversePalindrome.com
*/


#include "BodySerializer.hpp"

#include <Box2D/Dynamics/b2Fixture.h>


void BodySerializer::saveBody(const b2Body* body, pugi::xml_node& bodyNode)
{
    bodyNode.set_name("Body");

    bodyNode.append_attribute("type") = body->GetType();
    bodyNode.append_attribute("x") = body->GetPosition().x;
    bodyNode.append_attribute("y") = body->GetPosition().y;
    bodyNode.append_attribute("angle") = body->GetAngle();
    bodyNode.append_attribute("linearDamping") = body->GetLinearDamping();
    bodyNode.append_attribute("angularDamping") = body->GetAngularDamping();
    bodyNode.append_attribute("fixedRotation") = body->IsFixedRotation();
    bodyNode.append_attribute("bullet") = body->IsBullet();
}

void BodySerializer::saveFixture(const b2Fixture* fixture, pugi::xml_node& fixtureNode)
{
    fixtureNode.append_attribute("density") = fixture->GetDensity();
    fixtureNode.append_attribute("friction") = fixture->GetFriction();
    fixtureNode.append_attribute("restitution") = fixture->GetRestitution();
    fixtureNode.append_attribute("sensor") = fixture->IsSensor();
}

void BodySerializer::saveCircle(const b2CircleShape* circle, pugi::xml_node& circleNode)
{
    circleNode.set_name("Circle");
    circleNode.append_attribute("x") = circle->m_p.x;
    circleNode.append_attribute("y") = circle->m_p.y;
    circleNode.append_attribute("radius") = circle->m_radius;
}

void BodySerializer::saveEdge(const b2EdgeShape* edge, pugi::xml_node& edgeNode)
{
    edgeNode.set_name("Edge");

    edgeNode.append_attribute("hasVertex0") = edge->m_hasVertex0;
    edgeNode.append_attribute("hasVertex3") = edge->m_hasVertex3;

    if (edge->m_hasVertex0)
    {
        edgeNode.append_attribute("vertex0X") = edge->m_vertex0.x;
        edgeNode.append_attribute("vertex0Y") = edge->m_vertex0.y;
    }

    edgeNode.append_attribute("vertex1X") = edge->m_vertex1.x;
    edgeNode.append_attribute("vertex1Y") = edge->m_vertex1.y;
    edgeNode.append_attribute("vertex2X") = edge->m_vertex2.x;
    edgeNode.append_attribute("vertex2Y") = edge->m_vertex2.y;

    if (edge->m_hasVertex3)
    {
        edgeNode.append_attribute("vertex3X") = edge->m_vertex3.x;
        edgeNode.append_attribute("vertex3Y") = edge->m_vertex3.y;
    }
}

void BodySerializer::savePolygon(const b2PolygonShape* polygon, pugi::xml_node& polygonNode)
{
    polygonNode.set_name("Polygon");

    for (int i = 0; i < polygon->GetVertexCount(); ++i)
    {
        auto pointNode = polygonNode.append_child("Vertex");
        pointNode.append_attribute("x") = polygon->m_vertices[i].x;
        pointNode.append_attribute("y") = polygon->m_vertices[i].y;
    }
}

void BodySerializer::saveChain(const b2ChainShape* chain, pugi::xml_node& chainNode)
{
    chainNode.set_name("Chain");

    for (int i = 0; i < chain->m_count; ++i)
    {
        auto pointNode = chainNode.append_child("Vertex");
        pointNode.append_attribute("x") = chain->m_vertices[i].x;
        pointNode.append_attribute("y") = chain->m_vertices[i].y;
    }
}