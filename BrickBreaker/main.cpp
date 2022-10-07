// Written by Jaidon van Herwaarden
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include <JMath.h>

int main()
{
	GameConfig config{ "Jaidon's Brick Bonker!", 1280, 720 };
	Game BrickBonker(config);

	BrickBonker.Run();
	
	return 0;
}