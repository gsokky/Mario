#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 960

#define MAX_TURTLE_SPEED 12.0f
#define MARIO_JUMP_SPEED -22.0f
#define MAX_TURTLE_NUMBER 5
#define TURTLE_SPAWN_PERIOD 2.0f
#define RESPAWN_PROTECTION_TIME 2.0f