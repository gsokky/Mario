#include "Mario.h"

Mario::Mario()
{
	char path[64];
	for (int i = 0; i < 7; i++)
	{
		sprintf(path, "../assets/mario%d.png", i+1);
		textures[i].loadFromFile(path);
	}
	state = 1;
	heading = 0;	//left
	textures[7].loadFromFile("../assets/mariohead.png");
	sprite.setOrigin(textures[state].getSize().x / 2.0, textures[state].getSize().y / 2.0);
	sprite.setTexture(textures[state - 1]);
	objectSpeed = 12.0f;
	objectVerticalSpeed = 10.0f;
	vx = 0;
	vy = 0;
	dir = WalkDirection::Left;
	prevSide = 0;
	fallStatus = false;

	//scales the width and height of mario
	sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(textures[state-1].getSize().x * 32.0f / 2.0f), float(WINDOW_HEIGHT) / float(textures[state-1].getSize().y * 10)));
}

void Mario::move()
{
	switch (state)
	{
	case 1:
		if (dir == WalkDirection::Left)
		{
			(heading == 0 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = -objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 0;
		}
		else if (dir == WalkDirection::Right)
		{
			(heading == 1 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 1;
		}
		state = 2;
		break;
	case 2:
		if (dir == WalkDirection::Left)
		{
			(heading == 0 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = -objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 0;
		}
		else if (dir == WalkDirection::Right)
		{
			(heading == 1 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 1;
		}
		state = 3;
		break;
	case 3:
		if (dir == WalkDirection::Left)
		{
			(heading == 0 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = -objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 0;
		}
		else if (dir == WalkDirection::Right)
		{
			(heading == 1 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 1;
		}
		state = 4;
		break;
	case 4:
		if (dir == WalkDirection::Left)
		{
			(heading == 0 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = -objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 0;
		}
		else if (dir == WalkDirection::Right)
		{
			(heading == 1 ? sprite.scale(1.0f, 1.0f) : sprite.scale(-1.0f, 1.0f));
			vx = objectSpeed;
			sprite.move(Vector2f(vx, 0));
			heading = 1;
		}
		state = 2;
		break;
	}
	sprite.setTexture(textures[state - 1]);
}

void Mario::standStill()
{
	state = 1;
	vx = 0.0f;
	vy = 0.0f;
	sprite.setTexture(textures[state - 1]);
}
void Mario::fall()
{
	sprite.setTexture(textures[6]);
	sprite.move(Vector2f(0, objectVerticalSpeed));

	if (sprite.getPosition().y > WINDOW_HEIGHT + 5 * sprite.getGlobalBounds().height / 2.0f)
	{
		fallStatus = false;
		setPosition(Vector2f(WINDOW_WIDTH / 2.0f, float(WINDOW_HEIGHT * 19.0f / 25.0f)));
	}
	else
		fallStatus = true;
}

void Mario::jump(bool down)
{
	if (down)
	{
		sprite.setTexture(textures[5]);
		vy = objectVerticalSpeed;
		sprite.move(Vector2f(0, vy));
	}
	else
	{
		sprite.setTexture(textures[5]);
		sprite.move(Vector2f(0, vy));
	}
}