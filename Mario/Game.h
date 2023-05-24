#include "Common.h"
#include "Floor.h"
#include "Brick.h"
#include "Pipe.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Game {
	RenderWindow* window;
	int speed;
	Floor floor;
	Brick* bricks;
	Pipe* pipes;
	Object* objects;
	Mario* mario;
	Turtle* turtle;
	Mario* addMario(void);
	Turtle* addTurtle(void);
	bool jumpPeak = false;
	int side;
	ScoreBoard scoreboard;
	int score;
	Text text;
	Font font;

public:
	Game(int);
	void drawBackground(RenderWindow&);
	void update(void);
	~Game();
	void drawObjects(void);
	void removeObject(Object*);
	bool onFloor(Object*);
	bool checkSideIntersection(Object*, int);
	bool checkUpperIntersection(Object*);
	bool checkCollision(Turtle*, Mario*, int&);
	void drawScore(void);
	void drawLives(void);
	bool checkGameStatus(void);
	void menu(int);
	bool turtleCollision(Turtle*);

	};