#pragma once
#include "Common.h"
#include "Object.h"

class Mario : public Object {
public:
	WalkDirection dir;
	Mario();
	void move(void);
	void standStill(void);
	void fall(void);
	void jump(bool);
};