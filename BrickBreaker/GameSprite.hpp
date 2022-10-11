// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "GameCommon.hpp"

class GameSprite
{
public:
	GameSprite() = default;
	GameSprite(std::string filePath);

	void LoadTexture(std::string filePath);
	void SetPosition(float x, float y);

	// Is this weird? I don't know. I like it though
	void SetPosition(float yOrBoth, bool isXCentered = false);

	const sf::Sprite& GetDrawable() { return mSprite; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
};