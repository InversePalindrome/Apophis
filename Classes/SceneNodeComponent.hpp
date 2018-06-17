/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SceneNodeComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>

#include <pugixml.hpp>


class SceneNodeComponent
{
public:
	explicit SceneNodeComponent(const pugi::xml_node& componentNode);

	~SceneNodeComponent();

	cocos2d::Node* getRootSceneNode();
	cocos2d::Node* getRootSceneNode() const;

	cocos2d::Vec2 getRootSceneNodePosition() const;
	void setRootSceneNodePosition(const cocos2d::Vec2& position);

	float getRootSceneNodeRotation() const;
	void setRootSceneNodeRotation(float angle);

private:
	cocos2d::Node* rootSceneNode;

	void load(cocos2d::Node* parentSceneNode, const pugi::xml_node& sceneNodeData);
};