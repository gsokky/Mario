#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	texture.loadFromFile("../assets/mariohead.png");
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(WINDOW_WIDTH * 0.1f / 32.0f, WINDOW_HEIGHT * 1.0f / 25.0f));
	score = "000000";
	lives = 3;
}

void ScoreBoard::setScore(int score)
{
	char arr[7];
	snprintf(arr, sizeof(arr), "%06d", score);
	this->score = string(arr);
}

String ScoreBoard::getScore()
{
	return this->score;
}

void ScoreBoard::setLives(int lives)
{
	if (lives >= 0)
		this->lives = lives;
	else
		this->lives = 0;
}

int ScoreBoard::getLives()
{
	return this->lives;
}

