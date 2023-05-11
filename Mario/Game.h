#include "Common.h"
#include "Floor.h"
#include "Brick.h"
#include "Pipe.h"
#include "Mario.h"

class Game {
	RenderWindow* window;
	int speed;
	Floor floor;
	Brick* bricks;
	Pipe* pipes;
	Object* objects;
	Mario* mario;
	Mario* addMario(void);
	//Turtle* addTurtle(void);

public:
	Game(int);
	void drawBackground(RenderWindow&);
	void update(void);
	~Game();
	void drawObjects(void);
	void removeObject(Object*);
	bool onFloor(Object*);

};