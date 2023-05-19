#pragma once
#include "Common.h"

class Object {
	Vector2f pos;
	Object* next;
	friend class Game;
protected:
	Texture textures[8];
	Sprite sprite;
	int state;
	int heading;
	float objectSpeed;
	float objectVerticalSpeed;
	float vx;
	float vy;
	bool jumpStatus = false;
public:
	enum WalkDirection {
		Up,
		Down,
		Left,
		Right
	};
	bool onFloor = false;
	int prevSide;
	void setPosition(Vector2f);
	Vector2f getPosition();
	FloatRect boundingBox(void);
	void draw(RenderWindow*);
	virtual void move(void) = 0;
	virtual void fall(void) = 0;
	virtual void jump(bool) = 0;
	virtual ~Object() {

	}
};