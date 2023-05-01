#include "Game.h"

Game::Game()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	drawBackground(*window);
}

void Game::drawBackground(RenderWindow& window)
{
	//create bacground objects
	bricks = new Brick[7]{ Brick(12), Brick(12), Brick(4), Brick(4), Brick(16), Brick(14), Brick(14) };
	pipes = new Pipe[4]{ Pipe("pipe", false), Pipe("pipe", true), Pipe("pipeS", false), Pipe("pipeS", true) };

	//set the position of the created Floor object
	floor.setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 22.0 / 25.0)));	

	//set the position of each created Brick object
	bricks[0].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[1].setPosition(Vector2f(float(WINDOW_WIDTH * 20.0 / 32.0), float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[2].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[3].setPosition(Vector2f(float(WINDOW_WIDTH * 28.0 / 32.0), float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[4].setPosition(Vector2f(float(WINDOW_WIDTH * 8.0 / 32.0), float(WINDOW_HEIGHT * 12.0 / 25.0)));
	bricks[5].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 7.0 / 25.0)));
	bricks[6].setPosition(Vector2f(float(WINDOW_WIDTH * 18.0 / 32.0), float(WINDOW_HEIGHT * 7.0 / 25.0)));

	//set the position of each created Pipe object
	pipes[0].setPosition(Vector2f(float(WINDOW_WIDTH * 7.0 / 8.0), float(WINDOW_HEIGHT * 20.0 / 25.0)));
	pipes[1].setPosition(Vector2f(float(WINDOW_WIDTH * 1.0 / 16.0), float(WINDOW_HEIGHT * 21.0 / 25.0)));
	pipes[2].setPosition(Vector2f(float(WINDOW_WIDTH * 0.0), float(WINDOW_HEIGHT * 3.0 / 25.0)));
	pipes[3].setPosition(Vector2f(float(WINDOW_WIDTH * 29.0 / 32.0), float(WINDOW_HEIGHT * 4.5 / 25.0)));
}

void Game::update(void)
{
	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}
		
		window->clear();

		//draw bacground objects
		floor.draw(window);

		for (int i = 0; i < 7; i++)
			bricks[i].draw(window);

		for (int i = 0; i < 4; i++) 
			pipes[i].draw(window);
		
		window->display();

		sf::sleep(sf::milliseconds(1000));
	}
}