// Written by Jaidon van Herwaarden October 2022

#pragma once

// Engine dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// STL
#include <vector>

// Game
#include "GameConstants.hpp"
#include "GameState.hpp"

// Game Objects
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class PlayState : public GameState
{
public:
	PlayState() = default;

	void Initialize() override;
	void Terminate() override; 
	// deltaTime is measures in seconds.
	void Update(float deltaTime) override;
	void Render() override;

private:

	void CheckCollisions();

	sf::Music levelSong{};

	// Game Objects
	Paddle mPaddle{};
	Ball mBall{};
	std::vector<Brick> mBricks{};

	bool isNoClip = false;
	sf::Time secondsToTime;
	sf::Time currentElapsed;
	sf::Clock noClipTimer;
};