#include "Game.h"

Game::Game(int speed)
{
	this->speed = speed;
	window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO");
	drawBackground(*window);

	mario = addMario();
	mario->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, float(WINDOW_HEIGHT * 19.0f / 25.0f)));
	side = 0;
	score = 0;

	font.loadFromFile("../assets/font.ttf");
	text.setFont(font);

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
	Clock clock;	// starts the clock for turtle spawn
	Clock clock2;	// starts the clock for mario's protection after respawning
	int marioDir = 0;
	bool moving_up = false;
	bool moving_right = false;
	bool moving_left = false;
	int turtleNumber = 0;

	while (window->isOpen())
	{
		Time elapsed = clock.getElapsedTime();

		if (elapsed.asSeconds() > TURTLE_SPAWN_PERIOD && turtleNumber < MAX_TURTLE_NUMBER)
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
				turtle->turtleDir = 0;
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
					marioDir = 0;
				}
				else if (!moving_left && event.key.code == (sf::Keyboard::Right))
				{
					moving_right = true;
					marioDir = 1;
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
		if (!checkGameStatus()) // if the game is over, stop the game execution
		{
			//set the horizontal velocity as 0 if it intersects any background object from side or the window borders
			checkSideIntersection(mario, marioDir);
			if (!mario->fallStatus) {

				if (moving_up == true && mario->onFloor)
				{
					if (mario->jumpStatus == false) {
						mario->vy = MARIO_JUMP_SPEED;
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
			}
			// check for collisions between turtles and mario
			Object* tur = objects;
			while (tur)
			{
				if (tur != mario)
				{
					if (checkCollision(dynamic_cast<Turtle*>(tur), mario, side) || mario->fallStatus || tur->fallStatus)
					{
						if (side == 0 || tur->fallStatus)	//mario jumps on turtle
						{
							tur->fall();
							if (!tur->fallStatus)
							{
								score += 100;
								scoreboard.setScore(score);
								removeObject(tur);
								break;
							}
						}
						if (side == 1 || mario->fallStatus)
						{
							// if it has been 2 seconds since the last spawn of mario
							if (clock2.getElapsedTime().asSeconds() > RESPAWN_PROTECTION_TIME) {
								mario->fall();
								if (!mario->fallStatus)
								{
									// if mario  has fallen down, take his one live
									scoreboard.setLives(scoreboard.getLives() - 1);
									clock2.restart();
								}
							}
							break;
						}
					}
				}
				tur = tur->next;
			}

			Object* cur = objects;
			while (cur)
			{
				//check if the turtles collide with a background object
				if (dynamic_cast<Turtle*>(cur) && !dynamic_cast<Turtle*>(cur)->fallStatus)
				{
					if (checkSideIntersection(cur, dynamic_cast<Turtle*>(cur)->turtleDir))
					{
						dynamic_cast<Turtle*>(cur)->sideCollision = true;
						//if all turtles are created, increase their speed each time they change direction
						if (turtleNumber == 5 && abs(cur->vx) < MAX_TURTLE_SPEED)
							cur->vx += (cur->vx > 0 ? 0.1f : -0.1f);
					}
					else
						dynamic_cast<Turtle*>(cur)->sideCollision = false;

					cur->move();
				}

				//// turtle collision
				//if (dynamic_cast<Turtle*>(cur)) {
				//	if (turtleCollision(dynamic_cast<Turtle*>(cur)))
				//		dynamic_cast<Turtle*>(cur)->sideCollision = true;
				//	else
				//		dynamic_cast<Turtle*>(cur)->sideCollision = false;

				//}

				// check if the objects are on ground or falling
				if (!onFloor(cur) && !cur->fallStatus)
				{
					if (!cur->jumpStatus)	//falling
					{
						cur->jump(true);
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
					cur->jumpStatus = false;
				}

				cur = cur->next;
			}
		}
		else
		{
			// stop the game and return to menu
			return;
		}
		window->clear();

		checkGameStatus();

		//draw bacground objects
		floor.draw(window);

		for (int i = 0; i < 7; i++)
			bricks[i].draw(window);

		for (int i = 0; i < 4; i++) 
			pipes[i].draw(window);

		drawObjects();

		drawLives();

		drawScore();

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
		if (!(dynamic_cast<Turtle*>(cur) && !dynamic_cast<Turtle*>(cur)->isObjectVisible))
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
	if (floor.sprite.getPosition().y - obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2.0f < obj->objectVerticalSpeed && 
		!obj->jumpStatus)
	{
		if (obj->vy > 0)
		{
			//stop falling when hit the floor and set the correct texture
			obj->vy = 0;
			if(dynamic_cast<Mario*>(obj) != NULL)
				dynamic_cast<Mario*> (obj)->standStill();
		}
		obj->onFloor = true;
		return true;

	}
	for (int i = 0; i < 7; i++)
	{
		if ((bricks[i].sprite.getPosition().y - obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2.0f < obj->objectVerticalSpeed) &&
			(bricks[i].sprite.getPosition().y - obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2.0f >= 0) &&
			(bricks[i].sprite.getPosition().x <= obj->sprite.getPosition().x + obj->sprite.getGlobalBounds().width / 2.0f) &&
			(bricks[i].sprite.getPosition().x + bricks[i].sprite.getGlobalBounds().width >= obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2.0f) &&
			!obj->jumpStatus)
		{
			if (obj->vy > 0)
			{
				//stop falling when hit the floor and set the correct texture
				obj->vy = 0;
				if (dynamic_cast<Mario*>(obj) != NULL)
					dynamic_cast<Mario*> (obj)->standStill();
			}
			obj->onFloor = true;
			return true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if ((pipes[i].sprite.getPosition().y - obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2.0f < obj->objectVerticalSpeed) &&
			(pipes[i].sprite.getPosition().y - obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2.0f >= 0) &&
			(pipes[i].sprite.getPosition().x <= obj->sprite.getPosition().x + obj->sprite.getGlobalBounds().width / 2.0f) &&
			(pipes[i].sprite.getPosition().x + pipes[i].sprite.getGlobalBounds().width >= obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2.0f) &&
			!obj->jumpStatus)
		{
			if (obj->onFloor || obj->vy > 0)
			{
				if (obj->vy > 0)
				{
					//stop falling when hit the floor and set the correct texture
					obj->vy = 0.0f;
					if (dynamic_cast<Mario*>(obj) != NULL)
						dynamic_cast<Mario*> (obj)->standStill();
				}
				obj->onFloor = true;
				return true;
			}
		}
	}
	obj->onFloor = false;
	return false;
		
}

bool Game::checkSideIntersection(Object* obj, int s)
{
	if (dynamic_cast<Turtle*>(obj))
		dynamic_cast<Turtle*>(obj)->isObjectVisible = true;

	int pipeNo = -1;

	//check pipe intersections
	for (int i = 0; i < 4; i++) 
	{		
		if (obj->boundingBox().intersects(pipes[i].boundingBox()) && s == obj->prevSide)
		{
			if (dynamic_cast<Turtle*>(obj)) 
			{
				dynamic_cast<Turtle*>(obj)->isObjectVisible = false;
				pipeNo = i;
			}
			else 
			{
				obj->objectSpeed = 0.0f;
				obj->prevSide = s;
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
		if (dynamic_cast<Turtle*>(obj) && !dynamic_cast<Turtle*>(obj)->isObjectVisible)
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

bool Game::checkCollision(Turtle* t, Mario* m, int& side)
{
	if ((t->sprite.getPosition().y - t->sprite.getGlobalBounds().height / 2.0f - m->sprite.getPosition().y - m->sprite.getGlobalBounds().height / 2.0f < m->objectVerticalSpeed) &&
		(t->sprite.getPosition().y - t->sprite.getGlobalBounds().height / 2.0f - m->sprite.getPosition().y - m->sprite.getGlobalBounds().height / 2.0f >= 0) &&
		((t->sprite.getPosition().x - t->sprite.getGlobalBounds().width / 2.0f) <= m->sprite.getPosition().x + m->sprite.getGlobalBounds().width / 2.0f) &&
		(t->sprite.getPosition().x + t->sprite.getGlobalBounds().width / 2.0f >= m->sprite.getPosition().x - m->sprite.getGlobalBounds().width / 2.0f))
	{
		side = 0;
		return true;
	}
	else if (m->boundingBox().intersects(t->boundingBox()) && !t->fallStatus) 
	{
		side = 1;
		return true;
	}
	else
		return false;
}

void Game::drawScore()
{
	text.setString(scoreboard.getScore());
	text.setCharacterSize(24);
	text.setStyle(Text::Bold);

	window->draw(text);
}

void Game::drawLives()
{
	scoreboard.sprite.setTextureRect(IntRect(0, 0, scoreboard.texture.getSize().x * scoreboard.getLives(), scoreboard.texture.getSize().y));
	window->draw(scoreboard.sprite);
}

bool Game::checkGameStatus()
{
	if (score == MAX_TURTLE_NUMBER * 100)
	{
		text.setString("You win!");
		text.setCharacterSize(72);
		text.setStyle(Text::Bold);
		window->draw(text);
		return true;
	}
	else if (scoreboard.getLives() == 0)
	{
		text.setString("Game Over");
		text.setCharacterSize(72);
		text.setStyle(Text::Bold);
		window->draw(text);
		return true;
	}
	else
		return false;
}

void Game::menu(int speed)
{
	Clock clock;
	while (window->isOpen()) 
	{
		window->clear();
		text.setString("Start a new game (Enter)\n\nExit (Esc)");
		text.setCharacterSize(36);
		text.setStyle(Text::Bold);
		window->draw(text);
		window->display();

		Event event;
		while (true)
		{
			if (window->pollEvent(event))
			{
				if (Event::Closed)
					window->close();

				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == (sf::Keyboard::Enter))
						break;
					else if (event.key.code == (sf::Keyboard::Escape))
						window->close();
				}
			}
		}

		update();
		// clear all objects from the window
		Object* cur = objects;
		while (cur)
		{
			removeObject(cur);
			cur = objects;
		}

		// set the initial condition
		scoreboard.setScore(0);
		scoreboard.setLives(3);
		this->speed = speed;

		// set mario
		mario = addMario();
		mario->setPosition(Vector2f(WINDOW_WIDTH / 2.0f, float(WINDOW_HEIGHT * 19.0f / 25.0f)));
		side = 0;
		score = 0;
		
		clock.restart();
		while (clock.getElapsedTime().asSeconds() < 3.0f);	// wait for 3 seconds to return to menu
	}
}

bool Game::turtleCollision(Turtle* t)
{
	Object* tur = objects;
	while (tur)
	{
		if (dynamic_cast<Turtle*>(tur) && tur != t)
		{
			if ((t->sprite.getPosition().y - tur->sprite.getPosition().y < t->objectVerticalSpeed) &&
				t->turtleDir != dynamic_cast<Turtle*>(tur)->turtleDir)
			{
				if (t->turtleDir == 0 &&
					t->sprite.getPosition().x - t->boundingBox().width / 2.0f - (tur->sprite.getPosition().x + tur->boundingBox().width / 2.0f) < t->objectSpeed)
				{

					return true;
				}
				else if (t->turtleDir == 1 &&
					tur->sprite.getPosition().x - tur->boundingBox().width / 2.0f - (t->sprite.getPosition().x + t->boundingBox().width / 2.0f) < t->objectSpeed)
				{

					return true;
				}
			}
		}
		tur = tur->next;
	}
	return false;
}