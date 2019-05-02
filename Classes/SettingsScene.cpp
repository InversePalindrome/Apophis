/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SettingsScene.cpp
InversePalindrome.com
*/


#include "AppSettings.hpp"
#include "SettingsScene.hpp"

#include <CreatorReader.h>

#include <cocos/ui/UIButton.h>
#include <cocos/ui/UISlider.h>
#include <cocos/base/CCDirector.h>


cocos2d::Scene* getSettingsScene()
{
    auto* reader = creator::CreatorReader::createWithFilename("Creator/Scenes/Settings.ccreator");
    reader->setup();

    auto& appSettings = AppSettings::getInstance();

    auto* scene = reader->getSceneGraph();
    auto* canvas = scene->getChildByName("Canvas");
    auto* director = cocos2d::Director::getInstance();

    static_cast<cocos2d::ui::Button*>(canvas->getChildByName("backButton"))->addTouchEventListener([director](auto * sender, auto event)
        {
            director->popScene();
        });

    auto* soundVolumeSlider = static_cast<cocos2d::ui::Slider*>(canvas->getChildByName("soundSlider"));
    soundVolumeSlider->setPercent(static_cast<int>(appSettings.getSoundVolume() * 100));
    soundVolumeSlider->addClickEventListener([soundVolumeSlider, &appSettings](auto * sender) { appSettings.setSoundVolume(soundVolumeSlider->getPercent() / 100.f); });

    auto * musicVolumeSlider = static_cast<cocos2d::ui::Slider*>(canvas->getChildByName("musicSlider"));
    musicVolumeSlider->setPercent(static_cast<int>(appSettings.getMusicVolume() * 100));
    musicVolumeSlider->addClickEventListener([musicVolumeSlider, &appSettings](auto * sender) { appSettings.setMusicVolume(musicVolumeSlider->getPercent() / 100.f); });

    return scene;
}