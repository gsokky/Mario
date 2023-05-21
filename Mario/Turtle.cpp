#include "Turtle.h"

Turtle::Turtle()
{
	char path[64];
	for (int i = 0; i < 5; i++)
	{
		sprintf(path, "../assets/turtle%d.png", i + 1);
		textures[i].loadFromFile(path);
	}
	state = 1;
	heading = 0;	//left
	sprite.setOrigin(textures[state].getSize().x / 2.0, textures[state].getSize().y / 2.0);
	sprite.setTexture(textures[state - 1]);
	objectSpeed = 6.0f;
	objectVerticalSpeed = 7.0f;
	vx = objectSpeed;
	vy = 0;
	sideCollision = false;
	prevSide = 1;
	turtleDir = 1;
	fallStatus = false;

	//scales the width and height of turtles
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(textures[state - 1].getSize().x * 32.0f / 2.0f), float(WINDOW_HEIGHT) / float(textures[state - 1].getSize().y * 25.0f / 2.0f)));
}

void Turtle::move()
{
	switch (state)
	{
	case 1:
		if (sideCollision)
		{
			sprite.scale(-1.0f, 1.0f);
			vx = -vx;
			turtleDir ^= 1;
		}
		sprite.move(Vector2f(vx, 0));
		state = 2;
		break;
	case 2:
		if (sideCollision)
		{
			sprite.scale(-1.0f, 1.0f);
			vx = -vx;
			turtleDir ^= 1;
		}
		sprite.move(Vector2f(vx, 0));
		state = 3;
		break;
	case 3:
		if (sideCollision)
		{
			sprite.scale(-1.0f, 1.0f);
			vx = -vx;
			turtleDir ^= 1;
		}
		sprite.move(Vector2f(vx, 0));
		state = 1;
		break;
	}
	sprite.setTexture(textures[state - 1]);
}

void Turtle::fall()
{
	sprite.setTexture(textures[4]);
	sprite.move(Vector2f(0, objectVerticalSpeed));

	if (sprite.getPosition().y > WINDOW_HEIGHT + sprite.getGlobalBounds().height / 2.0f)
		fallStatus = false;

	else
		fallStatus = true;
}

void Turtle::jump(bool down)
{
	if (down)
	{
		vy = objectVerticalSpeed;
		sprite.move(Vector2f(0, vy));
	}
	else
		return;
}