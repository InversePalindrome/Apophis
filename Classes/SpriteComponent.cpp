/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"

#include <imgui.h>

#include <cocos/base/ccUtils.h>
#include <cocos/2d/CCSpriteFrameCache.h>


SpriteComponent::SpriteComponent() :
    NodeComponent(cocos2d::Sprite::create()),
    sprite(static_cast<cocos2d::Sprite*>(getNode())),
    repeatTexture(false)
{
}

void SpriteComponent::load(const pugi::xml_node& componentNode)
{
    NodeComponent::load(componentNode);

    if (const auto filenameAttribute = componentNode.attribute("filename"))
    {
        initWithFilename(filenameAttribute.as_string());
    }
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

    if (!filename.empty())
    {
        componentNode.append_attribute("filename") = filename.c_str();
    }
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

        filename.resize(64);
        if (ImGui::InputText("Filename", filename.data(), filename.length()))
        {
            initWithFilename(filename);
        }
        filename.erase(std::find(std::begin(filename), std::end(filename), '\0'), std::end(filename));

        spriteFrameName.resize(64);
        if (ImGui::InputText("Sprite Frame Name", spriteFrameName.data(), spriteFrameName.length()))
        {
            setSpriteFrame(spriteFrameName.c_str());
        }
        spriteFrameName.erase(std::find(std::begin(spriteFrameName), std::end(spriteFrameName), '\0'), std::end(spriteFrameName));

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

void SpriteComponent::initWithFilename(const std::string& filename)
{
    this->filename = filename;

    sprite->initWithFile(filename);
}

cocos2d::SpriteFrame* SpriteComponent::getSpriteFrame() const
{
    return sprite->getSpriteFrame();
}

void SpriteComponent::setSpriteFrame(const std::string& spriteFrameName)
{
    this->spriteFrameName = spriteFrameName;

    if (cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName))
    {
        sprite->setSpriteFrame(spriteFrameName);
    }
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