/*
Copyright (c) 2018 Inverse Palindrome
Apophis - NodeComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>


class NodeComponent
{
public:
	explicit NodeComponent(cocos2d::Node* node);
	~NodeComponent();

	void addChild(cocos2d::Node* child);
	void removeChild(cocos2d::Node* child);

	cocos2d::Action* runAction(cocos2d::Action* action);
	void stopAction(cocos2d::Action* action);

	cocos2d::Node* getNode();
	cocos2d::Node* getNode() const;

	cocos2d::Vec2 getScale() const;
	void setScale(const cocos2d::Vec2& scale);

	cocos2d::Size getContentSize() const;
	void setContentSize(const cocos2d::Size& contentSize);

	cocos2d::Vec2 getPosition() const;
	void setPosition(const cocos2d::Vec2& position);

	float getRotation() const;
	void setRotation(float angle);

	cocos2d::Color3B getColor() const;
	void setColor(const cocos2d::Color3B& color);

private:
	cocos2d::Node* node;
};