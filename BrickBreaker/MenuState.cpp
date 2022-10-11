// Written by Jaidon van Herwaarden October 2022

#include "MenuState.hpp"

#include <SFML/Window/Mouse.hpp>

#include "Game.hpp"

void MenuState::Initialize()
{
	LOG("Initializing MenuState.");

	ASSERT(titleSong.openFromFile("resources\\title.wav"), std::exception{ "File not found." });
	titleSong.setVolume(30.f);
	titleSong.setLoop(true);
	titleSong.play();

	mLogo.LoadTexture("resources\\logo.png");
	mLogo.SetPosition(100.0f, true);

	mEarth.LoadTexture("resources\\earth.png");
	mEarth.SetPosition(275.f, true);
	mEarth.GetSprite().setColor({ 150u, 150u, 150u });

	mPlayButton.LoadTexture("resources\\play.png");
	mPlayButton.SetPosition(350.0f, true);
	mPlayButton.SetColour(sf::Color::Green);

	mQuitButton.LoadTexture("resources\\quit.png");
	mQuitButton.SetPosition(550.0f, true);
	mQuitButton.SetColour(sf::Color::Red);

	Game::Get()->GetRenderWindow()->setMouseCursorVisible(true);
}

void MenuState::Terminate()
{
	LOG("Terminating MenuState.");
	titleSong.stop();
}

void MenuState::Update(float deltaTime)
{
	if (mPlayButton.Update())
	{
		auto game = Game::Get();
		game->ChangeState("PlayState");
	}
	else if (mQuitButton.Update())
	{
		auto game = Game::Get();
		game->Quit();
	}
}

void MenuState::Render()
{
	mLogo.Render();
	mEarth.Render();
	mPlayButton.Render();
	mQuitButton.Render();
}