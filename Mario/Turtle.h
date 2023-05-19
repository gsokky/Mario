#pragma once
#include "Common.h"
#include "Object.h"

class Turtle : public Object {
public:
	bool sideCollision;
	int side;
	bool setObjectVisible = true;
	Turtle();
	void move(void);
	void fall(void);
	void jump(bool);
};