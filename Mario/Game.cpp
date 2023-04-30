#include "Game.h"

Game::Game()
{
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	bricks = new Brick[7];

	bricks[0].setBrickNumber(12);
	bricks[1].setBrickNumber(12);
	bricks[2].setBrickNumber(4);
	bricks[3].setBrickNumber(4);
	bricks[4].setBrickNumber(16);
	bricks[5].setBrickNumber(14);
	bricks[6].setBrickNumber(14);

	drawBackground(*window);
}

void Game::drawBackground(RenderWindow& window)
{
	floor.setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 22.0 / 25.0)));
	/*cout << "test1" << endl; 
	bricks[0] = Brick(12);
	cout << "test2" << endl;
	bricks[1] = Brick(12);
	cout << "test3" << endl;
	bricks[2] = Brick(4);
	cout << "test4" << endl;
	bricks[3] = Brick(4);
	cout << "test5" << endl;
	bricks[4] = Brick(16);
	cout << "test6" << endl;
	bricks[5] = Brick(14);
	cout << "test7" << endl;
	bricks[6] = Brick(14);*/
	
	bricks[0].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[1].setPosition(Vector2f(float(WINDOW_WIDTH * 20.0 / 32.0), float(WINDOW_HEIGHT * 17.0 / 25.0)));
	bricks[2].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[3].setPosition(Vector2f(float(WINDOW_WIDTH * 28.0 / 32.0), float(WINDOW_HEIGHT * 13.0 / 25.0)));
	bricks[4].setPosition(Vector2f(float(WINDOW_WIDTH * 8.0 / 32.0), float(WINDOW_HEIGHT * 12.0 / 25.0)));
	bricks[5].setPosition(Vector2f(0.0f, float(WINDOW_HEIGHT * 7.0 / 25.0)));
	bricks[6].setPosition(Vector2f(float(WINDOW_WIDTH * 18.0 / 32.0), float(WINDOW_HEIGHT * 7.0 / 25.0)));

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

		window->display();

		sf::sleep(sf::milliseconds(1000));
	}
}