#include "Brick.h"

Brick::Brick(int brickNumber)
{
	texture.loadFromFile("../assets/brick.png");
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, texture.getSize().x * brickNumber, texture.getSize().y));

	//scales the width of each brick to fit a total of 32 bricks on the window horizontally, and also the height
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 32), float(WINDOW_HEIGHT) / float(texture.getSize().y * 25)));
}