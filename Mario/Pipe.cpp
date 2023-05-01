#include "Pipe.h"

Pipe::Pipe(){}

Pipe::Pipe(String text, bool rotate)
{
	if (text == "pipe")
	{
		texture.loadFromFile("../assets/pipe.png");
		sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 8), float(WINDOW_HEIGHT) / float(texture.getSize().y * 12.5)));
		if (rotate == true)
		{
			sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
			sprite.scale(-1.0f, 1.0f);
		}
		sprite.setTexture(texture);

	}
	else if (text == "pipeS")
	{
		texture.loadFromFile("../assets/pipeS.png");
		sprite.setScale(Vector2f(float(WINDOW_WIDTH) / float(texture.getSize().x * 32.0 / 6.0), float(WINDOW_HEIGHT) / float(texture.getSize().y * 25.0 / 3.0)));

		if (rotate == true)
		{
			sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
			sprite.scale(-1.0f, 1.0f);
		}
		sprite.setTexture(texture);
	}
	else
		throw "invalid pipe type";
}