// Written by Jaidon van Herwaarden October 2022

#include "GameSprite.hpp"
#include "Game.hpp"

GameSprite::GameSprite(std::string filePath)
{
	LoadTexture(filePath);
}

void GameSprite::Render()
{
	Game::Get()->GetRenderWindow()->draw(mSprite);
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

// Assumes the origin is top left.
void GameSprite::SetPosition(float yOrBoth, bool isXCentered)
{
	if (isXCentered)
	{
		const auto size = mTexture.getSize();
		auto& gameConfig = Game::Get()->GetGameConfig();

		// Assuming an origin of top left.
		mSprite.setPosition({ (gameConfig.mWindowWidth / 2.f) - (size.x / 2.f), yOrBoth });
		return;
	}
	mSprite.setPosition(yOrBoth, yOrBoth);
}