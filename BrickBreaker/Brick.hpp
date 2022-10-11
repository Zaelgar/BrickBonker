// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "GameCommon.hpp"
#include "GameSprite.hpp"

class Alien
{
public:
	void Initialize();
	void Update();
	void Render();
	void Shutdown();

	//const sf::RectangleShape GetRectangleShape() const { return mRectangleShape; }
	const sf::FloatRect GetGlobalBounds() const { return mSprite.GetGlobalBounds(); }

	//void SetColour(sf::Color colour);
	void SetPosition(float x, float y);
	void SetActive(bool isActive) { mIsActive = isActive; }

	bool IsActive() { return mIsActive; }
private:
	//sf::RectangleShape mRectangleShape{{
	//	GameConstants::BrickWidth,
	//	GameConstants::BrickHeight
	//}};

	GameSprite mSprite{};

	bool mIsActive = true;
};