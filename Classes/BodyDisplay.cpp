/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyDisplay.cpp
InversePalindrome.com
*/


#include "BodyDisplay.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


void BodyDisplay::displayBody(b2Body* body)
{
	const char* bodyTypes[] = { "Static", "Kinematic", "Dynamic" };

	if (auto bodyType = static_cast<int>(body->GetType()); ImGui::Combo("Type", &bodyType, bodyTypes, 3))
	{
		body->SetType(static_cast<b2BodyType>(bodyType));
	}
	if (auto position = body->GetPosition(); ImGui::InputFloat2("Position(X, Y)", &position.x))
	{
		body->SetTransform(position, body->GetAngle());
	}
	if (auto angle = body->GetAngle(); ImGui::InputFloat("Angle", &angle))
	{
		body->SetTransform(body->GetPosition(), angle);
	}
	if (auto linearDamping = body->GetLinearDamping(); ImGui::InputFloat("Linear Damping", &linearDamping))
	{
		body->SetLinearDamping(linearDamping);
	}
	if (auto angularDamping = body->GetAngularDamping(); ImGui::InputFloat("Angular Damping", &angularDamping))
	{
		body->SetAngularDamping(angularDamping);
	}
	if (auto rotationFixed = body->IsFixedRotation(); ImGui::Checkbox("Rotation Fixed", &rotationFixed))
	{
		body->SetFixedRotation(rotationFixed);
	}
	if (auto bullet = body->IsBullet(); ImGui::Checkbox("Bullet", &bullet))
	{
		body->SetBullet(bullet);
	}
}

void BodyDisplay::displayFixture(b2Fixture* fixture)
{
	if (auto density = fixture->GetDensity(); ImGui::InputFloat("Density", &density))
	{
		fixture->SetDensity(density);
	}
	if (auto friction = fixture->GetFriction(); ImGui::InputFloat("Friction", &friction))
	{
		fixture->SetFriction(friction);
	}
	if (auto restitution = fixture->GetRestitution(); ImGui::InputFloat("Restitution", &restitution))
	{
		fixture->SetRestitution(restitution);
	}
	if (auto sensor = fixture->IsSensor(); ImGui::Checkbox("Sensor", &sensor))
	{
		fixture->SetSensor(sensor);
	}
}

void BodyDisplay::displayCircle(b2CircleShape& circle)
{
	ImGui::InputFloat("Radius", &circle.m_radius);
	ImGui::InputFloat2("Center", &circle.m_p.x);
}

void BodyDisplay::displayCircle(const b2CircleShape* circle)
{
	if (ImGui::TreeNode("Circle"))
	{
		ImGui::Text("Radius: %.2f", circle->m_radius);
		ImGui::Text("Center(X, Y): (%.2f, %.2f)", circle->m_p.x, circle->m_p.y);

		ImGui::TreePop();
	}
}

void BodyDisplay::displayEdge(b2EdgeShape& edge)
{
	ImGui::Checkbox("Has Vertex 0", &edge.m_hasVertex0);
	ImGui::SameLine();
	ImGui::Checkbox("Has Vertex 3", &edge.m_hasVertex3);

	if (edge.m_hasVertex0)
	{
		ImGui::InputFloat2("Vertex 0", &edge.m_vertex0.x);
	}

	ImGui::InputFloat2("Vertex 1", &edge.m_vertex1.x);
	ImGui::InputFloat2("Vertex 2", &edge.m_vertex2.x);

	if (edge.m_hasVertex3)
	{
		ImGui::InputFloat2("Vertex 3", &edge.m_vertex3.x);
	}
}

void BodyDisplay::displayEdge(const b2EdgeShape* edge)
{
	if (ImGui::TreeNode("Edge"))
	{
		if (edge->m_hasVertex0)
		{
			ImGui::Text("Vertex 0(X, Y): (%.2f, %.2f)", edge->m_vertex0.x, edge->m_vertex0.y);
		}

		ImGui::Text("Vertex 1(X, Y): (%.2f, %.2f)", edge->m_vertex1.x, edge->m_vertex1.y);
		ImGui::Text("Vertex 2(X, Y): (%.2f, %.2f)", edge->m_vertex2.x, edge->m_vertex2.y);

		if (edge->m_hasVertex3)
		{
			ImGui::Text("Vertex 3(X, Y): (%.2f, %.2f)", edge->m_vertex3.x, edge->m_vertex3.y);
		}

		ImGui::TreePop();
	}
}

void BodyDisplay::displayPolygon(const b2PolygonShape* polygon)
{
	if (ImGui::TreeNode("Polygon"))
	{
		for (int i = 0; i < polygon->m_count; ++i)
		{
			ImGui::Text("Vertex %d (X, Y): (%.2f, %.2f)", i, polygon->m_vertices[i].x, polygon->m_vertices[i].y);
		}

		ImGui::TreePop();
	}
}

void BodyDisplay::displayChain(const b2ChainShape* chain)
{
	if (ImGui::TreeNode("Chain"))
	{
		for (int i = 0; i < chain->m_count; ++i)
		{
			ImGui::Text("Vertex %d (X, Y): (%.2f, %.2f)", i, chain->m_vertices[i].x, chain->m_vertices[i].y);
		}

		ImGui::TreePop();
	}
}

void BodyDisplay::displayVertices(std::vector<b2Vec2>& vertices)
{
	ImGui::Text("Vertices");
	ImGui::SameLine();

	if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
	{
		vertices.push_back({ 0.f, 0.f });
	}

	int i = 0;

	for (auto vertexItr = std::begin(vertices); vertexItr != std::end(vertices);)
	{
		ImGui::PushID(i++);
		
		ImGui::InputFloat2("Vertex", &vertexItr->x);
		
		ImGui::SameLine();
		if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
		{
			vertexItr = vertices.erase(vertexItr);
		}
		else
		{
			++vertexItr;
		}

		ImGui::PopID();
	}
}