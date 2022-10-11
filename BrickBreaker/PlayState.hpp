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

	// TODO1: Stars are kind of hacky. Compartmentalize them into objects?
	void InitializeStars();
	void UpdateStars();
	sf::Vector2f RandomStarPosition();
	void RenderStars(sf::RenderWindow* renderWindow);

	sf::Music levelSong{};
	PauseMenu mPauseMenu{};

	// Game Objects
	Paddle mPaddle{};
	Ball mBall{};
	std::vector<Alien> mBricks{};
	sf::RectangleShape mLeftWall{};
	sf::RectangleShape mTopWall{};
	sf::RectangleShape mRightWall{};
	GameSprite mEarth{};

	// Transparent stripes
	unsigned int starCount = 20;
	sf::Color mStarColour{ 100u, 100u, 100u, 50u };
	sf::Vector2f mStarSize{15.f, 200.f};
	float mStarSpeed = 20.f;
	std::vector<sf::RectangleShape> mStars{};

	unsigned int mActiveBrickCounter = 0;
	bool mIsPaused = false;
};