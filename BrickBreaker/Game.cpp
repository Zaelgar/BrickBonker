// Written by Jaidon van Herwaarden October 2022

#include "Game.hpp"

#include <thread>

#include "GameState.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"

namespace
{
	std::unique_ptr<Game> sGameInstance = nullptr;
}

Game::Game(GameConfig gameConfig)
	: mGameConfig(gameConfig)
{
	if (sGameInstance == nullptr)
	{
		LOG("Initializing Game Instance.");
		sGameInstance.reset(this);
	}

	LOG("Initializing SFML RenderWindow.");
	// TODO2: why doesn't this like the initializer list when a member instead of a ptr?
	mRenderWindow = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(mGameConfig.mWindowWidth, mGameConfig.mWindowHeight)
		, mGameConfig.gameName
		, mGameConfig.WindowStyle);

	mRenderWindow->setFramerateLimit(mGameConfig.maxFPS);

	AddState<MenuState>("MenuState");
	AddState<PlayState>("PlayState");
}

Game::~Game()
{
	sGameInstance.release();
}

Game* Game::Get()
{
	if (sGameInstance != nullptr)
	{
		return sGameInstance.get();
	}
	return nullptr;
}

void Game::ChangeState(std::string name)
{
	if (auto iter = mGameStates.find(name); iter != mGameStates.end())
	{
		mNextState = iter->second.get();
		mIsEscapeHitThisFrame = false;
	}
	else
	{
		LOG("There was no state called: " + name + ". Exiting game.");
		Quit();
	}
}

void Game::Run()
{
	mCurrentState = mGameStates.begin()->second.get();
	mCurrentState->Initialize();

	sf::Time deltaTime;
	deltaTime = mClock.restart();

	while (mRenderWindow->isOpen())
	{
		mIsEscapeHitThisFrame = false;
		sf::Event event;
		while (mRenderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Quit();
			}
			// We only want to let 1 full press of the escape key through. Holding it down doesn't count.
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Escape)
			{
				mIsEscapeHitThisFrame = true;
			}
		}

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
			deltaTime = mClock.restart();
		}

		mCurrentState->Update(deltaTime.asSeconds());

		mRenderWindow->clear();
		mCurrentState->Render();
		mRenderWindow->display();

		deltaTime = mClock.restart();
	}
}

void Game::Quit()
{
	mCurrentState->Terminate();
	mRenderWindow->close();
}

bool Game::IsEscapeHitThisFrame(bool isConsumed)
{
	if (mIsEscapeHitThisFrame && isConsumed)
	{
		mIsEscapeHitThisFrame = false;
		return true;
	}
	return mIsEscapeHitThisFrame;
}