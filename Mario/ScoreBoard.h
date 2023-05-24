#include "Common.h"

class ScoreBoard {
	string score;
	int lives;
	friend class Mario;
public:
	Texture texture;
	Sprite sprite;
	ScoreBoard();
	void setScore(int);
	String getScore(void);
	void setLives(int);
	int getLives(void);

};