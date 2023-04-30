#include "Pipe.h"

Pipe::Pipe()
{
	texture.loadFromFile("../assets/pipe.png");
	sprite.setTexture(texture);

	//scales width and height of the floor to fit in window
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 8), float(WINDOW_HEIGHT) / float(texture.getSize().y * 12.5)));
}
