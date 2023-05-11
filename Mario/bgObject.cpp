#include "bgObject.h"

void bgObject::setPosition(Vector2f pos)
{
	this->pos = pos;
	sprite.setPosition(pos);
}

void bgObject::draw(RenderWindow* window)
{
	window->draw(sprite);
}

FloatRect bgObject::boundingBox()
{
	return sprite.getGlobalBounds();
}