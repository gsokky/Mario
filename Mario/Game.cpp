#include "Game.h"

Game::Game(int speed)
{
	this->speed = speed;
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	drawBackground(*window);

	mario = addMario();
	mario->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, float(WINDOW_HEIGHT * 19.0f / 25.0f)));
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
	Clock clock;	// starts the clock
	int side = 0;
	bool moving_up = false;
	bool moving_right = false;
	bool moving_left = false;
	int turtleNumber = 0;

	while (window->isOpen())
	{
		Time elapsed = clock.getElapsedTime();

		if (elapsed.asSeconds() > 5.0f && turtleNumber < 5)
		{
			turtle = addTurtle();
			++turtleNumber;

			if (turtleNumber % 2 == 1)
				turtle->setPosition(Vector2f(WINDOW_WIDTH * 7.0f / 32.0f, WINDOW_HEIGHT * 4.0f / 25.0f));
			else
			{
				turtle->setPosition(Vector2f(WINDOW_WIDTH * 25.0f / 32.0f, WINDOW_HEIGHT * 4.0f / 25.0f));
				turtle->vx = -turtle->objectSpeed;
				turtle->prevSide = 0;
				turtle->side = 0;
				turtle->sprite.scale(-1.0f, 1.0f);
			}
			clock.restart();
		}

		Event event;
		window->setKeyRepeatEnabled(false);
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				if (!moving_right && event.key.code == (sf::Keyboard::Left))
				{
					moving_left = true;
					side = 0;
				}
				else if (!moving_left && event.key.code == (sf::Keyboard::Right)) 
				{
					moving_right = true;
					side = 1;
				}

				if (event.key.code == (sf::Keyboard::Up)) {
					moving_up = true;
				}
				break;

			case Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Right)
					moving_right = false;

				else if (event.key.code == sf::Keyboard::Left)
					moving_left = false;

				if (event.key.code == sf::Keyboard::Up)
					moving_up = false;

				//if mario is not moving set the state as 1
				if (mario->jumpStatus == false)
					mario->standStill();
				break;

			case Event::Closed:
				window->close();
				break;

			default:
				break;
			}
		}

		//set the horizontal velocity as 0 if it intersects any background object from side or the window borders
		checkSideIntersection(mario, side);

		if (moving_up == true && mario->onFloor)
		{
			cout << "up" << endl;
			if (mario->jumpStatus == false) {
				mario->vy = -3.2f * mario->objectVerticalSpeed;
			}

			mario->jumpStatus = true;
		}

		if (moving_right == true)
		{
			mario->dir = Mario::WalkDirection::Right;
			mario->move();
		}
		else if (moving_left == true)
		{
			mario->dir = Mario::WalkDirection::Left;
			mario->move();
		}

		// check if the objects are on ground or falling
		Object* cur = objects;
		while (cur)
		{

			if (dynamic_cast<Turtle*>(cur))
			{
				if (checkSideIntersection(cur, dynamic_cast<Turtle*>(cur)->side))
					dynamic_cast<Turtle*>(cur)->sideCollision = true;
				else
					dynamic_cast<Turtle*>(cur)->sideCollision = false;

				cur->move();
			}

			if (!onFloor(cur))
			{
				if (!cur->jumpStatus)	//falling
				{
					cur->jump(true);
					cout << "jumpdown" << endl;
				}
				else
				{
					if (checkUpperIntersection(cur))
						continue;

					if (cur->vy < 0)	//jumping
					{
						cur->vy += 1;	//decreasing vertical speed until the peak point
						cur->jump(false);
					}
					else
					{
						cur->jumpStatus = false;
					}
				}
			}
			else
			{
				cout << "dont jump domw" << endl;
				cur->jumpStatus = false;
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
		//if the object is a turtle and not visible(in pipe) do not draw
		if (!(dynamic_cast<Turtle*>(cur) && !dynamic_cast<Turtle*>(cur)->setObjectVisible))
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
			if (floor.sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f < cur->objectVerticalSpeed && 
				!cur->jumpStatus)
			{
				cout << "floor intersect" << endl;
				if (cur->vy > 0)
				{
					//stop falling when hit the floor and set the correct texture
					cur->vy = 0;
					if(dynamic_cast<Mario*>(cur) != NULL)
						dynamic_cast<Mario*> (cur)->standStill();
				}
				cur->onFloor = true;
				return true;

			}
			for (int i = 0; i < 7; i++)
			{
				if ((bricks[i].sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f < cur->objectVerticalSpeed) &&
					(bricks[i].sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f >= 0) &&
					(bricks[i].sprite.getPosition().x <= cur->sprite.getPosition().x + cur->sprite.getGlobalBounds().width / 2.0f) &&
					(bricks[i].sprite.getPosition().x + bricks[i].sprite.getGlobalBounds().width >= cur->sprite.getPosition().x - cur->sprite.getGlobalBounds().width / 2.0f) &&
					!cur->jumpStatus)
				{
					cout << "bricks intersect " << i << endl;
					cout << bricks[i].sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f << endl;
					if (cur->vy > 0)
					{
						//stop falling when hit the floor and set the correct texture
						cur->vy = 0;
						if (dynamic_cast<Mario*>(cur) != NULL)
							dynamic_cast<Mario*> (cur)->standStill();
					}
					cur->onFloor = true;
					return true;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if ((pipes[i].sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f < cur->objectVerticalSpeed) &&
					(pipes[i].sprite.getPosition().y - cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height / 2.0f >= 0) &&
					(pipes[i].sprite.getPosition().x <= cur->sprite.getPosition().x + cur->sprite.getGlobalBounds().width / 2.0f) &&
					(pipes[i].sprite.getPosition().x + pipes[i].sprite.getGlobalBounds().width >= cur->sprite.getPosition().x - cur->sprite.getGlobalBounds().width / 2.0f) &&
					!cur->jumpStatus)
				{
					cout << "pipes intersect " << i << endl;
					if (cur->onFloor || cur->vy > 0)
					{
						if (cur->vy > 0)
						{
							//stop falling when hit the floor and set the correct texture
							cur->vy = 0.0f;
							if (dynamic_cast<Mario*>(cur) != NULL)
								dynamic_cast<Mario*> (cur)->standStill();
						}
						cur->onFloor = true;
						return true;
					}
				}
			}
			cur->onFloor = false;
			return false;
		}
		cur = cur->next;
	}
}

bool Game::checkSideIntersection(Object* obj, int s)
{
	if (dynamic_cast<Turtle*>(obj))
		dynamic_cast<Turtle*>(obj)->setObjectVisible = true;

	int pipeNo = -1;

	//check pipe intersections
	for (int i = 0; i < 4; i++) 
	{
		//cout << "piperight"<<i<<": "<< pipes[i].boundingBox().left + pipes[i].boundingBox().width << endl;
		//cout << "pipeleft" << i << ": " << pipes[i].boundingBox().left << endl;
		//cout << "dist pipe" <<i <<": " << abs(obj->boundingBox().left - (pipes[i].boundingBox().left + pipes[i].boundingBox().width)) << endl;;
		
		if (obj->boundingBox().intersects(pipes[i].boundingBox()) && s == obj->prevSide)
		{
			if (dynamic_cast<Turtle*>(obj)) 
			{
				dynamic_cast<Turtle*>(obj)->setObjectVisible = false;
				pipeNo = i;
			}
			else 
			{
				obj->objectSpeed = 0.0f;
				obj->prevSide = s;
				cout << "pipe side" << endl;
				return true;
			}
		}
		else 
		{
			obj->objectSpeed = 12.0f;
		}
	}

	//check brick intersections
	for (int i = 0; i < 7; i++)
	{
		if (!obj->onFloor && obj->boundingBox().intersects(bricks[i].boundingBox()) && s == obj->prevSide)
		{
			obj->objectSpeed = 0.0f;
			obj->prevSide = s;
			cout << "brick side" << endl;
			return true;
		}
		else
		{
			obj->objectSpeed = 12.0f;
		}
	}

	//check window border intersections
	if ((obj->sprite.getPosition().x - obj->boundingBox().width / 2.0f <= 0 ||
		obj->sprite.getPosition().x + obj->boundingBox().width / 2.0f >= WINDOW_WIDTH) &&
		s == obj->prevSide)
	{
		//check if a turtle enters in a pipe and teleport it to the upper pipes
		if (dynamic_cast<Turtle*>(obj) && !dynamic_cast<Turtle*>(obj)->setObjectVisible)
		{
			if (pipeNo == 0)
			{
				obj->setPosition(Vector2f(WINDOW_WIDTH * 7.0f / 32.0f, WINDOW_HEIGHT * 4.0f / 25.0f));
				return false;
			}
			if (pipeNo == 1)
			{
				obj->setPosition(Vector2f(WINDOW_WIDTH * 25.0f / 32.0f, WINDOW_HEIGHT * 4.0f / 25.0f));
				return false;
			}
		}
		obj->objectSpeed = 0.0f;
		obj->prevSide = s;
		cout << "out of window" << endl;
		return true;
	}
	else
	{
		obj->objectSpeed = 12.0f;
	}
	obj->prevSide = s;
	return false;
}

bool Game::checkUpperIntersection(Object* obj)
{
	for (int i = 0; i < 7; i++)
	{
		if (!obj->onFloor && obj->boundingBox().intersects(bricks[i].boundingBox()))
		{
			obj->jumpStatus = false;
			return true;
		}
	}

	if (obj->sprite.getPosition().y - obj->boundingBox().height / 2.0f <= 0)
	{
		obj->jumpStatus = false;
		return true;
	}
	return false;
}

Turtle* Game::addTurtle(void)
{
	Turtle* turtle = new Turtle();
	turtle->next = objects;
	objects = turtle;
	return turtle;
}