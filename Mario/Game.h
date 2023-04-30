#include "Common.h"
#include "Floor.h"
#include "Brick.h"
#include "Pipe.h"

class Game {
	RenderWindow* window;
	Floor floor;
	Brick* bricks;
	Pipe pipes;

public:
	Game();
	void drawBackground(RenderWindow&);
	void update(void);
};