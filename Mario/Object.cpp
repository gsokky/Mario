#include "Object.h"

void Object::setPosition(Vector2f pos)
{
	this->pos = pos;
	sprite.setPosition(pos);
}

Vector2f Object::getPosition()
{
	return pos;
}

void Object::draw(RenderWindow* window)
{
	window->draw(sprite);
}

FloatRect Object::boundingBox()
{
	return sprite.getGlobalBounds();
}
