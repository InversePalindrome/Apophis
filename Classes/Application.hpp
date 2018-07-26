/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Application.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/platform/CCApplication.h>


class Application : public cocos2d::Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator= (const Application&) = delete;

	~Application();

	virtual bool applicationDidFinishLaunching() override;
	virtual void applicationDidEnterBackground() override;
	virtual void applicationWillEnterForeground() override;
};
