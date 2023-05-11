#include "Game.h"

Game::Game(int speed)
{
	this->speed = speed;
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	drawBackground(*window);

	mario = addMario();
	mario->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, float(WINDOW_HEIGHT * 1.0 / 25.0)));
	/*for (int i; i < NUM_TURTLES; i++)
	{
		Turtle* turtle = addTurtle();
		turtle->setPosition...
	}*/

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
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					mario->move(Mario::WalkDirection::Left);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					mario->move(Mario::WalkDirection::Right);
				}
			}
			else if (event.type == Event::KeyReleased)
			{
				//if mario is not moving sets the state as 1
				mario->standStill();
			}
		}
		
		Object* cur = objects;
		while (cur)
		{
			if (!onFloor(cur))
			{
				mario->jump(true);
			}
			cur = cur->next;
		}

		window->clear();

		//draw bacground objects
		floor.draw(window);

		for (int i = 0; i < 7; i++)
			bricks[i].draw(window);

		for (int i = 0; i < 4; i++) 
			pipes[i].draw(window);

		drawObjects();

		window->display();

		sf::sleep(sf::milliseconds(1000/speed));
	}
}

Game::~Game()
{
	if (bricks != NULL)
		delete[] bricks;
	if (pipes != NULL)
		delete[] pipes;
}

Mario* Game::addMario(void)
{
	Mario* mario = new Mario();
	mario->next = objects;
	objects = mario;
	return mario;
}

void Game::drawObjects(void)
{
	Object* cur = objects;
	while (cur)
	{
		cur->draw(window);
		cur = cur->next;
	}
}

void Game::removeObject(Object* obj)
{
	Object* cur = objects;
	Object* prev = NULL;
	while (cur)
	{
		if (cur == obj) {
			if (prev)
				prev->next = cur->next;
			else
				objects = cur->next;
			delete cur;
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

bool Game::onFloor(Object* obj)
{
	Object* cur = objects;
	while (cur)
	{
		if (cur == obj) 
		{
			if (cur->boundingBox().intersects(floor.boundingBox()))
			{
				if (cur->vy > 0)
					cur->vy = 0;	//stops falling when hit the floor
				return true;
			}
			for (int i = 0; i < 7; i++)
			{
				if (cur->boundingBox().intersects(bricks[i].boundingBox())) 
				{
					if (cur->vy > 0)
						cur->vy = 0;	//stops falling when hit the floor
					if (cur->boundingBox().left == ( bricks[i].boundingBox().left + bricks[i].boundingBox().width ) && cur->heading == 0)
						cur->objectSpeed = 0.0f;
					else
						cur->objectSpeed = 12.0f;
					return true;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (cur->boundingBox().intersects(pipes[i].boundingBox()))
				{
					if (cur->vy > 0)
						cur->vy = 0;	//stops falling when hit the floor
					if (cur->boundingBox().left == (pipes[i].boundingBox().left + pipes[i].boundingBox().width) && cur->heading == 0) {
						cur->objectSpeed = 0.0f;
					}
					else
						cur->objectSpeed = 12.0f;
					return true;
				}
			}
			return false;
		}
		cur = cur->next;
	}
}