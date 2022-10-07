// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "Debug.h"

class GameSprite
{
public:
	GameSprite() = default;
	GameSprite(std::string filePath);

	void LoadTexture(std::string filePath);
	void SetPosition(float x, float y);

	const sf::Sprite& GetDrawable() { return mSprite; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
};