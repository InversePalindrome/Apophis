/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SceneNodeComponent.cpp
InversePalindrome.com
*/


#include "SceneNodeComponent.hpp"

#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCParticleSystemQuad.h>


SceneNodeComponent::SceneNodeComponent(const pugi::xml_node& componentNode) :
	rootSceneNode(cocos2d::Node::create())
{
	load(rootSceneNode, componentNode);
	
	rootSceneNode->retain();
}

SceneNodeComponent::~SceneNodeComponent()
{
	rootSceneNode->removeFromParent();
	rootSceneNode->removeAllChildren();
}

cocos2d::Node* SceneNodeComponent::getRootSceneNode()
{
	return rootSceneNode;
}

cocos2d::Node* SceneNodeComponent::getRootSceneNode() const
{
	return rootSceneNode;
}

cocos2d::Vec2 SceneNodeComponent::getRootSceneNodePosition() const
{
	return rootSceneNode->getPosition();
}

void SceneNodeComponent::setRootSceneNodePosition(const cocos2d::Vec2& position)
{
	rootSceneNode->setPosition(position);
}

float SceneNodeComponent::getRootSceneNodeRotation() const
{
	return rootSceneNode->getRotation();
}

void SceneNodeComponent::setRootSceneNodeRotation(float angle)
{
	rootSceneNode->setRotation(angle);
}

void SceneNodeComponent::load(cocos2d::Node* parentSceneNode, const pugi::xml_node& sceneNodeData)
{
	for (const auto childSceneNodeData : sceneNodeData.children())
	{
		if (std::strcmp(childSceneNodeData.name(), "Sprite") == 0)
		{
			auto* sprite = cocos2d::Sprite::createWithSpriteFrameName(childSceneNodeData.text().as_string());

			parentSceneNode->addChild(sprite);

			load(sprite, childSceneNodeData);
		}
		else if (std::strcmp(childSceneNodeData.name(), "Particle") == 0)
		{
			auto* particle = cocos2d::ParticleSystemQuad::create(std::string(childSceneNodeData.text().as_string()) + ".plist");

			parentSceneNode->addChild(particle);

			load(particle, childSceneNodeData);
		}
	}
}