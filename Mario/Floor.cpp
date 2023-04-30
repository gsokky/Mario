#include "Floor.h"

Floor::Floor()
{
	texture.loadFromFile("../assets/floor.png");
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x), 1.0f));	//scales width of the floor to fit in window
}
