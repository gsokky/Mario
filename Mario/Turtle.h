#pragma once
#include "Common.h"
#include "Object.h"

class Turtle : public Object {
public:
	bool sideCollision;
	int turtleDir;
	bool isObjectVisible = true;
	Turtle();
	void move(void);
	void fall(void);
	void jump(bool);
};