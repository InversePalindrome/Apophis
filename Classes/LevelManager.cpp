/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelManager.cpp
InversePalindrome.com
*/


#include "LevelManager.hpp"

#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


LevelManager& LevelManager::getInstance()
{
    static LevelManager instance;

    return instance;
}

void LevelManager::load(const std::string& filename)
{
    if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
    {
        if (const auto levelsNode = doc.child("Levels"))
        {
            for (const auto levelNode : levelsNode.children("Level"))
            {
                if (const auto filenameAttribute = levelNode.attribute("filename"))
                {
                    addLevel(filenameAttribute.as_string());
                }
            }
        }
    }
}

void LevelManager::save(const std::string& filename) const
{
    pugi::xml_document doc;

    auto declaration = doc.append_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";
    declaration.append_attribute("encoding") = "UTF-8";

    auto levelsNode = doc.append_child("Levels");

    for (const auto& level : levels)
    {
        auto levelNode = levelsNode.append_child("Level");
        levelNode.append_attribute("filename") = level.c_str();
    }

    doc.save_file(filename.c_str());
}

void LevelManager::addLevel(const std::string& level)
{
    levels.push_back(level);
}

void LevelManager::removeLevel(std::size_t index)
{
    levels.erase(std::begin(levels) + index);
}

void LevelManager::clearLevels()
{
    levels.clear();
}

std::size_t LevelManager::getLevelCount() const
{
    return levels.size();
}

std::string& LevelManager::operator[](std::size_t index)
{
    return levels[index];
}

const std::string& LevelManager::operator[](std::size_t index) const
{
    return levels[index];
}