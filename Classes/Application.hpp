/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - Application.hpp
InversePalindrome.com
*/


#pragma once

#include <CCApplication.h>


class Application : public cocos2d::Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator= (const Application&) = delete;

	virtual bool applicationDidFinishLaunching() override;
	virtual void applicationDidEnterBackground() override;
	virtual void applicationWillEnterForeground() override;

private:
	void createSearchPaths();

	void initSpriteFrames();
};
