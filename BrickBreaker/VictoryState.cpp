// Written by Jaidon van Herwaarden October 2022

#include "VictoryState.h"
#include "Game.hpp"

void VictoryState::Initialize()
{
	LOG("Initializing VictoryState.");

	const auto& gameConfig = Game::Get()->GetGameConfig();

	mVictorySprite.LoadTexture("resources\\victory.png");
	mVictorySprite.SetPosition(100.f, true);

	mHeroButton.LoadTexture("resources\\hero.png");
	mHeroButton.SetPosition(350.f, true);
	mHeroButton.SetColour(sf::Color::Green);

	// TODO2: Refactor into game sound object just like sprite
	ASSERT(mVictorySoundBuffer.loadFromFile("resources\\victory.wav"), std::exception("File not found."));
	mVictoryNoise.setBuffer(mVictorySoundBuffer);
	mVictoryNoise.play();
}

void VictoryState::Terminate()
{
	LOG("Terminating VictoryState.");
	mVictoryNoise.stop();
}

void VictoryState::Update(float deltaTime)
{
	if (mHeroButton.Update())
	{
		Game::Get()->ChangeState("MenuState");
	}
}

void VictoryState::Render()
{
	mVictorySprite.Render();
	mHeroButton.Render();
}