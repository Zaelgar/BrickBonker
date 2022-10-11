// Written by Jaidon van Herwaarden October 2022

#include "DefeatState.h"
#include "Game.hpp"

void DefeatState::Initialize()
{
	LOG("Initializing DefeatState.");
	const auto& gameConfig = Game::Get()->GetGameConfig();

	mDefeatSprite.LoadTexture("resources\\defeat.png");
	mDefeatSprite.SetPosition(100.f, true);

	mFailureButton.LoadTexture("resources\\failure.png");
	mFailureButton.SetPosition(350.f, true);
	mFailureButton.SetColour(sf::Color::Red);

	// TODO2: Refactor into game sound object just like sprite
	ASSERT(mDefeatSoundBuffer.loadFromFile("resources\\defeat.wav"), std::exception("File not found."));
	mDefeatNoise.setBuffer(mDefeatSoundBuffer);
	mDefeatNoise.play();

	Game::Get()->GetRenderWindow()->setMouseCursorVisible(true);
}

void DefeatState::Terminate()
{
	LOG("Terminating DefeatState.");
	mDefeatNoise.stop();
}

void DefeatState::Update(float deltaTime)
{
	if (mFailureButton.Update())
	{
		Game::Get()->ChangeState("MenuState");
	}
}

void DefeatState::Render()
{
	mDefeatSprite.Render();
	mFailureButton.Render();
}