// Written by Jaidon van Herwaarden

#pragma once

// SFML
#include <SFML/Graphics.hpp>
// TODO3: SFML has a weird issue when destroying audio.
// Not sure if it's me or the library. I tried giving sleep time
// But that wasn't enough for it to close properly. sf::Music
#include <SFML/Audio.hpp>

// Game
#include "GameConstants.hpp"
#include <JMath.h>
#include "Debug.hpp"

// STL
#include <string>

// TODO2: I don't know if this structuring is proper.
// The GameCommon.hpp is included in a lot of files, and I 
// think it might be better included inside of .cpp files
// rather than .h files.