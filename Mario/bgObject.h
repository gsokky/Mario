#pragma once
#include "Common.h"

class bgObject {
	Vector2f pos;
protected:
	Texture texture;
	Sprite sprite;
public:
	void setPosition(Vector2f);
	void draw(RenderWindow*);
	FloatRect boundingBox(void);
};

