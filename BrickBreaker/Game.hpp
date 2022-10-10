// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include "Debug.h"
#include "GameState.hpp"
#include "GameConstants.hpp"

struct GameConfig
{
	GameConfig() = default;
	GameConfig(std::string name)
		:gameName(std::move(name))
	{}
	GameConfig(std::string name, uint32_t windowWidth, uint32_t windowHeight)
		:gameName(std::move(name))
	{
		if (windowWidth < 800 || windowWidth > 1920)
			mWindowWidth = 1280;
		else
			mWindowWidth = windowWidth;
		if (windowHeight < 600 || windowHeight > 1080)
			mWindowHeight = 720;
		else
			mWindowHeight = windowHeight;
	}

	std::string gameName = "NO_NAME";
	uint32_t mWindowWidth = 1280;
	uint32_t mWindowHeight = 720;
	uint32_t WindowStyle = sf::Style::Close | sf::Style::Titlebar;
	uint32_t maxFPS = 60;
};

class Game
{
public:
	Game() = delete;
	Game(const Game&&) = delete;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(GameConfig gameConfig);
	~Game();

	static Game* Get();

	void Run();
	void Quit();

	template <class StateType>
	void AddState(std::string name);

	void ChangeState(std::string name);

	sf::RenderWindow* GetRenderWindow() { return mRenderWindow.get(); }
	const GameConfig& GetGameConfig() const { return mGameConfig; }
	bool IsEscapeHitThisFrame(bool isConsumed = false);

private:
	std::map<std::string, std::unique_ptr<GameState>> mGameStates;

	// TODO2: Weird issue of initialization. No window showing when initialized
	// as a part of the initializer list
	std::unique_ptr<sf::RenderWindow> mRenderWindow{ nullptr };
	sf::Clock mClock{};

	GameConfig mGameConfig{};

	// Game State Machine
	GameState* mCurrentState{ nullptr };
	GameState* mNextState{ nullptr };

	bool mIsEscapeHitThisFrame = false;
};

template <class StateType>
void Game::AddState(std::string name)
{
	mGameStates.emplace(std::move(name), std::make_unique<StateType>());
}