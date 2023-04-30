#include "Brick.h"

Brick::Brick()
{
	texture.loadFromFile("../assets/brick.png");
	texture.setRepeated(true);
	sprite.setTexture(texture);
	
}

void Brick::setBrickNumber(int brickNumber)
{
	this->brickNumber = brickNumber;
	sprite.setTextureRect(IntRect(0, 0, texture.getSize().x * brickNumber, texture.getSize().y));
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 32), 1.0f));	//scales width of each brick to fit a total of 32 bricks on the window horizontally

}