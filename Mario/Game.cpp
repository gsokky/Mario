#include "Game.h"

Game::Game()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	bricks = new Brick[7];

	drawBackground(*window);
}

void Game::drawBackground(RenderWindow& window)
{
	floor.setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 22.0 / 25.0)));	
	bricks->initializeBricks(bricks);
	pipes.setPosition(Vector2f(float(WINDOW_WIDTH * 7.0 / 8.0), float(WINDOW_HEIGHT * 20.0 / 25.0)));
}
void Game::update(void)
{
	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window->close();
		}
		
		window->clear();

		floor.draw(window);

		for (int i = 0; i < 7; i++)
		{
			bricks[i].draw(window);
		}

		pipes.draw(window);

		window->display();

		sf::sleep(sf::milliseconds(1000));
	}
}