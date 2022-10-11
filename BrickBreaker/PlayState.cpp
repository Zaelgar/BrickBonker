// Written by Jaidon van Herwaarden October 2022

#include "Common.h"
#include "PlayState.hpp"
#include "Game.hpp"

void PlayState::Initialize()
{
	// Initialize music
	LOG("Initializing PlayState.");

	ASSERT(levelSong.openFromFile("resources\\level1song.wav"));
	levelSong.setVolume(30.f);
	levelSong.setLoop(true);
	levelSong.play();

	const GameConfig& gameConfig = Game::Get()->GetGameConfig();

	// Initialize Game Objects
	mPaddle.Initialize();
	mBall.Initialize();
	
	mEarth.LoadTexture("resources\\bigearth.png");
	auto& sprite = mEarth.GetSprite();

	InitializeStars();

	// Initialize walls
	mLeftWall.setFillColor(sf::Color::Blue);
	mLeftWall.setSize({ static_cast<float>(GameConstants::WallThickness), static_cast<float>(gameConfig.mWindowHeight) });
	mLeftWall.setPosition({ -(GameConstants::WallThickness / 2.f), 0.f });

	mTopWall.setFillColor(sf::Color::Blue);
	mTopWall.setSize({ static_cast<float>(gameConfig.mWindowWidth), static_cast<float>(GameConstants::WallThickness) });
	mTopWall.setPosition({ 0.f, -(GameConstants::WallThickness / 2.f) });

	mRightWall.setFillColor(sf::Color::Blue);
	mRightWall.setSize({ static_cast<float>(GameConstants::WallThickness), static_cast<float>(gameConfig.mWindowHeight) });
	mRightWall.setPosition({ gameConfig.mWindowWidth - (GameConstants::WallThickness / 2.f) }, 0.f);


	// Initialize brick layout
	// TODO2: Convert this to read in a CSV or JSON as a level? Makes Playstate more versatile
	int levelHeight = 5;
	int levelWidth = 10;
	mBricks.resize(levelHeight * levelWidth);
	mBricks.shrink_to_fit();
	float brickHeight = GameConstants::BrickHeight;
	float brickWidth = GameConstants::BrickWidth;
	float edgeOffset = 80.f;
	float offset = 13.3f;
	for (int y = 0; y < levelHeight; ++y)
	{
		for (int x = 0; x < levelWidth; ++x)
		{
			int i = x + y * levelWidth;

			mBricks[i].Initialize();
			mBricks[i].SetPosition(edgeOffset + ((brickWidth + offset) * x), edgeOffset + ((brickHeight + offset) * y));
			mBricks[i].SetActive(true);
		}
	}
	mActiveBrickCounter = levelHeight * levelWidth;

	// Initialize Pause Screen
	mPauseMenu.Initialize();
	mIsPaused = false;

	Game::Get()->GetRenderWindow()->setMouseCursorVisible(false);
}

void PlayState::Terminate()
{
	LOG("Terminating PlayState.");
	levelSong.stop();
}

void PlayState::Update(float deltaTime)
{
	Game::Get()->GetRenderWindow()->setMouseCursorVisible(mIsPaused);
	auto game = Game::Get();

	UpdateStars();

	if (mBall.CheckDeathCollision())
	{
		game->ChangeState("DefeatState");
	}

	if (Game::Get()->IsEscapeHitThisFrame(true))
	{
		mIsPaused = mIsPaused ? false : true;
	}

	if (!mIsPaused)
	{
		CheckCollisions();

		mPaddle.Update();
		mBall.Update();
	}
	else if (mPauseMenu.Update()) // Will return true if resume is pressed
	{
		mIsPaused = false;
	}

	if (!mActiveBrickCounter)
	{
		game->ChangeState("VictoryState");
	}
}

void PlayState::Render()
{
	auto renderWindow = Game::Get()->GetRenderWindow();

	RenderStars(renderWindow);

	// Draw Walls
	renderWindow->draw(mLeftWall);
	renderWindow->draw(mTopWall);
	renderWindow->draw(mRightWall);

	// Draw Bricks
	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			brick.Render();
		}
	}

	// Draw other game objects
	mPaddle.Render();
	mBall.Render();
	auto v = mEarth.GetGlobalBounds();
	mEarth.Render();


	// Only if paused, draw pause screen last (on top)
	if (mIsPaused)
	{
		mPauseMenu.Render();
	}
}

void PlayState::CheckCollisions()
{
	CollisionType collisionType = mBall.CheckRectCollision(mPaddle.GetGlobalBounds());

	if (collisionType != CollisionType::None)
	{
		auto paddleToBall = mBall.GetPosition() - mPaddle.GetPosition();
		mBall.SetVelocity(paddleToBall);
	}

	mActiveBrickCounter = 0;
	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			++mActiveBrickCounter;
			collisionType = mBall.CheckRectCollision(brick.GetGlobalBounds());

			if (collisionType == CollisionType::Left || collisionType == CollisionType::Right)
			{
				mBall.NegateXVelocity();
				brick.SetActive(false);
			}
			else if (collisionType == CollisionType::Top || collisionType == CollisionType::Bottom)
			{
				mBall.NegateYVelocity();
				brick.SetActive(false);
			}
		}
	}

	collisionType = mBall.CheckRectCollision(mLeftWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateXVelocity();
	}

	collisionType = mBall.CheckRectCollision(mRightWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateXVelocity();
	}

	collisionType = mBall.CheckRectCollision(mTopWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateYVelocity();
	}
}

void PlayState::InitializeStars()
{
	auto& gameConfig = Game::Get()->GetGameConfig();

	mStars.resize(starCount);
	std::vector<JMath::Vector2> positions{};
	JMath::RandomPointsInRectangle(positions
		, { 0.f, 0.f, static_cast<float>(gameConfig.mWindowWidth), static_cast<float>(gameConfig.mWindowHeight) }
		, starCount);

	for (size_t i = 0; i < starCount; ++i)
	{
		mStars[i].setFillColor(mStarColour);
		mStars[i].setSize(mStarSize);
		//mStars[i].setPosition(positions[i].x, positions[i].y);
		mStars[i].setPosition(RandomStarPosition());
	}
}

void PlayState::UpdateStars()
{
	for (auto& s : mStars)
	{
		s.move(0.f, -mStarSpeed);
		auto position = s.getPosition();
		if (s.getPosition().y < -mStarSize.y)
		{
			s.setPosition(s.getPosition().x, Game::Get()->GetGameConfig().mWindowHeight + mStarSize.y);
		}
	}
}

sf::Vector2f PlayState::RandomStarPosition()
{
	auto& gameConfig = Game::Get()->GetGameConfig();
	return { JMath::Random::RandomFloatUniform(0.f, gameConfig.mWindowWidth)
		, JMath::Random::RandomFloatUniform(0.f, gameConfig.mWindowHeight) };
}

void PlayState::RenderStars(sf::RenderWindow* renderWindow)
{
	for (auto& s : mStars)
	{
		renderWindow->draw(s);
	}
}