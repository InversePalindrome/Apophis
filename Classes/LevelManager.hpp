/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelManager.hpp
InversePalindrome.com
*/


#pragma once

#include <string>
#include <vector>


class LevelManager
{
public:
	LevelManager() = default;
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator= (const LevelManager&) = delete;

	static LevelManager& getInstance();

	void load(const std::string& filename);
	void save(const std::string& filename) const;

	void addLevel(const std::string& level);
	void removeLevel(std::size_t index);
	void clearLevels();

	std::size_t getLevelCount() const;

	std::string& operator[](std::size_t index);
	const std::string& operator[](std::size_t index) const;

private:
	std::vector<std::string> levels;
};
