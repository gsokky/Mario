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
	
	//scales width of each brick to fit a total of 32 bricks on the window horizontally, and also height
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 32), float(WINDOW_HEIGHT) / float(texture.getSize().y * 25)));

}

void Brick::initializeBricks(Brick* bricks)
{
	//sets the number of bricks in each floor starting from bottom to top
	bricks[0].setBrickNumber(12);
	bricks[1].setBrickNumber(12);
	bricks[2].setBrickNumber(4);
	bricks[3].setBrickNumber(4);
	bricks[4].setBrickNumber(16);
	bricks[5].setBrickNumber(14);
	bricks[6].setBrickNumber(14);

	//sets the positions of initialized brick floors
	bricks[0].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[1].setPosition(Vector2f(float(WINDOW_WIDTH * 20.0 / 32.0), float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[2].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[3].setPosition(Vector2f(float(WINDOW_WIDTH * 28.0 / 32.0), float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[4].setPosition(Vector2f(float(WINDOW_WIDTH * 8.0 / 32.0), float(WINDOW_HEIGHT * 12.0 / 25.0)));
	bricks[5].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 7.0 / 25.0)));
	bricks[6].setPosition(Vector2f(float(WINDOW_WIDTH * 18.0 / 32.0), float(WINDOW_HEIGHT * 7.0 / 25.0)));
}