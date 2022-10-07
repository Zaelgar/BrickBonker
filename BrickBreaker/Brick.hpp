// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>

#include "GameConstants.hpp"

class Brick
{
public:
	void Initialize();
	void Update();
	void Shutdown();

	const sf::RectangleShape GetDrawable() const;

	void SetColour(sf::Color colour);
	void SetPosition(float x, float y);

	bool IsActive() { return mIsActive; }
private:
	sf::RectangleShape mRectangleShape{{
		GameConstants::BrickWidth,
		GameConstants::BrickHeight
	}};

	bool mIsActive = true;
};