// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <vector>

#include "GameState.hpp"

// Game Objects
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"
#include "PauseMenu.hpp"

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
	PauseMenu mPauseMenu{};

	// Game Objects
	Paddle mPaddle{};
	Ball mBall{};
	std::vector<Brick> mBricks{};
	sf::RectangleShape mLeftWall{};
	sf::RectangleShape mTopWall{};
	sf::RectangleShape mRightWall{};

	bool mIsPaused = false;
};