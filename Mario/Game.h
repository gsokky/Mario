#include "Common.h"
#include "Floor.h"
#include "Brick.h"
//#include "Tunnel.h"

class Game {
	RenderWindow* window;
	Floor floor;
	Brick* bricks;
	//Tunnel tunnels;

public:
	Game();
	void drawBackground(RenderWindow&);
	void update(void);
};