/*
Copyright (c) 2018 Inverse Palindrome
Apophis - NodeComponent.cpp
InversePalindrome.com
*/


#include "NodeComponent.hpp"


NodeComponent::NodeComponent(cocos2d::Node* node, const pugi::xml_node& componentNode) :
	node(node)
{
	if (const auto xPositionAttribute = componentNode.attribute("x"))
	{
		node->setPositionX(xPositionAttribute.as_float());
	}
	if (const auto yPositionAttribute = componentNode.attribute("y"))
	{
		node->setPositionY(yPositionAttribute.as_float());
	}
	if (const auto rotationAttribute = componentNode.attribute("rotation"))
	{
		setRotation(rotationAttribute.as_float());
	}
	if (const auto xScaleAttribute = componentNode.attribute("xScale"))
	{
		node->setScaleX(xScaleAttribute.as_float());
	}
	if (const auto yScaleAttribute = componentNode.attribute("yScale"))
	{
		node->setScaleY(yScaleAttribute.as_float());
	}
	if (const auto rAttribute = componentNode.attribute("R"),
	    gAttribute = componentNode.attribute("G"),
	    bAttribute = componentNode.attribute("B");
	    rAttribute && gAttribute && bAttribute)
	{
		setColor(cocos2d::Color3B(rAttribute.as_uint(), gAttribute.as_uint(), bAttribute.as_uint()));
	}
	
	node->retain();
}

NodeComponent::~NodeComponent()
{
	node->removeFromParent();
	node->removeAllChildren();

	node->release();
}

void NodeComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.append_attribute("x") = getPosition().x;
	componentNode.append_attribute("y") = getPosition().y;
	componentNode.append_attribute("rotation") = getRotation();
	componentNode.append_attribute("xScale") = getScale().x;
	componentNode.append_attribute("yScale") = getScale().y;
	componentNode.append_attribute("R") = getColor().r;
	componentNode.append_attribute("G") = getColor().g;
	componentNode.append_attribute("B") = getColor().b;
}

void NodeComponent::addChild(cocos2d::Node* child)
{
	node->addChild(child);
}

void NodeComponent::removeChild(cocos2d::Node* child)
{
	node->removeChild(child);
}

cocos2d::Action* NodeComponent::runAction(cocos2d::Action* action)
{
	return node->runAction(action);
}

void NodeComponent::stopAction(cocos2d::Action* action)
{
	node->stopAction(action);
}

cocos2d::Node* NodeComponent::getNode()
{
	return node;
}

cocos2d::Node* NodeComponent::getNode() const
{
	return node;
}

cocos2d::Size NodeComponent::getContentSize() const
{
	return node->getContentSize();
}

void NodeComponent::setContentSize(const cocos2d::Size& contentSize)
{
	node->setContentSize(contentSize);
}

cocos2d::Vec2 NodeComponent::getScale() const
{
	return { node->getScaleX(), node->getScaleY() };
}

void NodeComponent::setScale(const cocos2d::Vec2& scale)
{
	node->setScale(scale.x, scale.y);
}

cocos2d::Vec2 NodeComponent::getPosition() const
{
	return node->getPosition();
}

void NodeComponent::setPosition(const cocos2d::Vec2& position)
{
	node->setPosition(position);
}

float NodeComponent::getRotation() const
{
	return node->getRotation();
}

void NodeComponent::setRotation(float angle)
{
	node->setRotation(angle);
}

cocos2d::Color3B NodeComponent::getColor() const
{
	return node->getColor();
}

void NodeComponent::setColor(const cocos2d::Color3B& color)
{
	node->setColor(color);
}

bool NodeComponent::isVisible() const
{
	return node->isVisible();
}

void NodeComponent::setVisible(bool visible)
{
	node->setVisible(visible);
}