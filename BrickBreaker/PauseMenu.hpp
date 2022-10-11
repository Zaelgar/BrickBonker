// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "Common.h"
#include "GameButton.hpp"

class PauseMenu
{
public:
	PauseMenu() = default;

	void Initialize();
	bool Update();
	void Render();

private:

	GameSprite mPauseSprite{};
	GameButton mPlayButton{};
	GameButton mQuitButton{};
	sf::RectangleShape mPauseUnderlay{};
	// Half transparent black screen
	sf::Color mPauseColour{ 0u, 0u, 0u, 128u };
};