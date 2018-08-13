/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"

#include <imgui.h>

#include <cocos/base/ccUtils.h>


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::Sprite::create(), componentNode),
	sprite(static_cast<cocos2d::Sprite*>(getNode())),
	repeatTexture(false)
{
	if (const auto spriteFrameAttribute = componentNode.attribute("frame"))
	{
		setSpriteFrame(spriteFrameAttribute.as_string());
	}
	if (const auto textureXAttribute = componentNode.attribute("textureX"),
	    textureYAttribute = componentNode.attribute("textureY"),
	    textureWidthAttribute = componentNode.attribute("textureWidth"),
	    textureHeightAttribute = componentNode.attribute("textureHeight"); 
	    textureXAttribute && textureYAttribute && textureWidthAttribute && textureHeightAttribute)
	{
		setTextureRect({ textureXAttribute.as_float(), textureYAttribute.as_float(), textureWidthAttribute.as_float(), textureHeightAttribute.as_float() });
	}
	if (const auto repeatAttribute = componentNode.attribute("repeat"))
	{
		setTextureRepeated(repeatAttribute.as_bool());
	}
}

void SpriteComponent::save(pugi::xml_node& componentNode) const
{
	NodeComponent::save(componentNode);
	
	componentNode.set_name("Sprite");
	
	if (!spriteFrameName.empty())
	{
		componentNode.append_attribute("frame") = spriteFrameName.c_str();
	}

	componentNode.append_attribute("textureX") = getTextureRect().origin.x;
	componentNode.append_attribute("textureY") = getTextureRect().origin.y;
	componentNode.append_attribute("textureWidth") = getTextureRect().size.width;
	componentNode.append_attribute("textureHeight") = getTextureRect().size.height;

	componentNode.append_attribute("repeat") = isTextureRepeated();
}

void SpriteComponent::display()
{
	if (ImGui::TreeNode("Sprite"))
	{
		NodeComponent::display();

		spriteFrameName.resize(64);
		if (ImGui::InputText("Sprite Frame Name", spriteFrameName.data(), spriteFrameName.length()))
		{
			setSpriteFrame(spriteFrameName);
		}
		if (auto textureRect = cocos2d::Vec4(getTextureRect().origin.x, getTextureRect().origin.y, getTextureRect().size.width, getTextureRect().size.height); ImGui::InputFloat4("Texture(X, Y, Width, Height)", &textureRect.x))
		{
			setTextureRect(cocos2d::Rect(textureRect.x, textureRect.y, textureRect.z, textureRect.w));
		}
		if (auto textureRepeat = isTextureRepeated(); ImGui::Checkbox("Texture Repeated", &textureRepeat))
		{
			setTextureRepeated(textureRepeat);
		}

		ImGui::TreePop();
	}
}

cocos2d::SpriteFrame* SpriteComponent::getSpriteFrame() const
{
	return sprite->getSpriteFrame();
}

void SpriteComponent::setSpriteFrame(const std::string& spriteFrameName)
{
	this->spriteFrameName = spriteFrameName;

	sprite->setSpriteFrame(spriteFrameName);
}

cocos2d::Texture2D* SpriteComponent::getTexture() const
{
	return sprite->getTexture();
}

void SpriteComponent::setTexture(cocos2d::Texture2D* texture)
{
	sprite->setTexture(texture);
}

cocos2d::Rect SpriteComponent::getTextureRect() const
{
	return sprite->getTextureRect();
}

void SpriteComponent::setTextureRect(const cocos2d::Rect& textureRect)
{
	sprite->setTextureRect(textureRect);
}

bool SpriteComponent::isTextureRepeated() const
{
	return repeatTexture;
}

void SpriteComponent::setTextureRepeated(bool repeatTexture)
{
	this->repeatTexture = repeatTexture;
	
	if (repeatTexture && 
		(getTexture()->getPixelsWide() & (getTexture()->getPixelsWide() - 1)) == 0 &&
		(getTexture()->getPixelsHigh() & (getTexture()->getPixelsHigh() - 1)) == 0)
	{
		getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
	}
} 