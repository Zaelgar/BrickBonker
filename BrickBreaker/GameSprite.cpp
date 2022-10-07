// Written by Jaidon van Herwaarden October 2022

#include "GameSprite.hpp"

GameSprite::GameSprite(std::string filePath)
{
	LoadTexture(filePath);
}

void GameSprite::LoadTexture(std::string filePath)
{
	ASSERT(mTexture.loadFromFile(filePath), std::exception{ "File not found." });
	mSprite.setTexture(mTexture);
}

void GameSprite::SetPosition(float x, float y)
{
	mSprite.setPosition(x, y);
}