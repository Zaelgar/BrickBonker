// Written by Jaidon van Herwaarden October 2022

#include "PauseMenu.hpp"
#include "Game.hpp"

void PauseMenu::Initialize()
{
	mPauseSprite.LoadTexture("resources\\paused.png");
	mPauseSprite.SetPosition(100.f, true);

	mPlayButton.LoadTexture("resources\\play.png");
	mPlayButton.SetPosition(250.0f, true);
	mPlayButton.SetColour(sf::Color::Green);

	mQuitButton.LoadTexture("resources\\quit.png");
	mQuitButton.SetPosition(450.f, true);
	mQuitButton.SetColour(sf::Color::Red);

	mPauseUnderlay.setSize({ static_cast<float>(Game::Get()->GetGameConfig().mWindowWidth)
		, static_cast<float>(Game::Get()->GetGameConfig().mWindowHeight) });
	mPauseUnderlay.setFillColor(mPauseColour);
}

bool PauseMenu::Update()
{
	if (mPlayButton.Update())
	{
		return true;
	}
	else if (mQuitButton.Update())
	{
		Game::Get()->ChangeState("MenuState");
	}

	return false;
}

void PauseMenu::Render()
{
	auto renderWindow = Game::Get()->GetRenderWindow();

	renderWindow->draw(mPauseUnderlay);

	mPauseSprite.Render();
	mPlayButton.Render();
	mQuitButton.Render();
}