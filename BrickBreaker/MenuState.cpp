// Written by Jaidon van Herwaarden October 2022

#include "MenuState.hpp"

#include <SFML/Window/Mouse.hpp>

#include "Game.hpp"

void MenuState::Initialize()
{
	LOG("Initializing MenuStateS.");

	ASSERT(titleSong.openFromFile("resources\\title.wav"), std::exception{ "File not found." });
	titleSong.setVolume(30.f);
	titleSong.setLoop(true);
	titleSong.play();

	mLogo.LoadTexture("resources\\logo.png");
	mLogo.SetPosition(180.0f, 100.0f);

	mPlayButton.LoadTexture("resources\\play.png");
	mPlayButton.SetPosition({ 550.0f, 350.0f });
	mPlayButton.SetColour(sf::Color::Green);

	mQuitButton.LoadTexture("resources\\quit.png");
	mQuitButton.SetPosition({ 565.0f, 550.0f });
	mQuitButton.SetColour(sf::Color::Red);
}

void MenuState::Terminate()
{
	LOG("Terminating MenuState.");
	titleSong.stop();
}

void MenuState::Update(float deltaTime)
{
	auto game = Game::Get();

	auto mousePosition = sf::Mouse::getPosition(*game->GetRenderWindow());

	if (mPlayButton.Update(mousePosition))
	{
		game->ChangeState("PlayState");
	}
	else if (mQuitButton.Update(mousePosition))
	{
		game->Quit();
	}
}

void MenuState::Render()
{
	auto renderWindow = Game::Get()->GetRenderWindow();

	renderWindow->draw(mLogo.GetDrawable());
	renderWindow->draw(mPlayButton.GetDrawable());
	renderWindow->draw(mQuitButton.GetDrawable());
}