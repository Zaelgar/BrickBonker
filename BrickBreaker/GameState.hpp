// Written by Jaidon van Herwaarden October 2022

#pragma once

class Game;

class GameState
{
public:
	GameState() = default;
	GameState(GameState&&) = delete;
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Initialize() = 0;
	virtual void Terminate() = 0;
	// deltaTime is measures in seconds.
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};