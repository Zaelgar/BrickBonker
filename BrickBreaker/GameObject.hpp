// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

	bool IsActive() const { return mIsActive; }

protected:
	bool mIsActive = true;
};