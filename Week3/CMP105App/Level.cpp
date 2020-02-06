#include "Level.h"
#include <stdlib.h>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	// circle
	circle.setRadius(15);
	circle.setPosition(20, 300);
	circle.setFillColor(sf::Color::Yellow);

	// rectangle
	rect.setSize(sf::Vector2f(30, 30));
	rect.setPosition(600, 333);
	rect.setFillColor(sf::Color::Black);

	// circle2
	circle2.setRadius(25);
	circle2.setPosition(20, 300);
	circle2.setFillColor(sf::Color::Green);

	circleSpeed = 400.f;
	rectSpeed = 0;
	circle2SpeedX = 250.f;
	circle2SpeedY = 250.f;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	// Rectangle's movement
	if (input->isKeyDown(sf::Keyboard::W))
	{
		rectSpeed = -100.f;
		rect.move(0, rectSpeed * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		rectSpeed = 100.f;
		rect.move(0, rectSpeed * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		rectSpeed = -100.f;
		rect.move(rectSpeed * dt, 0);
	}
	else if(input->isKeyDown(sf::Keyboard::D))
	{	
		rectSpeed = 100.f;
		rect.move(rectSpeed * dt, 0);
	}
	else
	{
		rectSpeed = 0.f;
	}

	if (input->isKeyDown(sf::Keyboard::Up))
	{
		circle2SpeedX = circle2SpeedX + 100.f;
		circle2SpeedY = circle2SpeedY + 100.f;
		input->setKeyUp(sf::Keyboard::Up);
	}
	else if (input->isKeyDown(sf::Keyboard::Down))
	{

		circle2SpeedX = circle2SpeedX - 100.f;
		circle2SpeedY = circle2SpeedY - 100.f;
		input->setKeyUp(sf::Keyboard::Down);

	}

}

// Update game objects
void Level::update(float dt)
{

	sf::Vector2u pos = window->getSize();
	sf::Vector2f circlePos = circle.getPosition();
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f circle2Pos = circle2.getPosition();

	
	// Update the circle.
	if (circlePos.x > (pos.x -30))
	{
		circleSpeed = -circleSpeed;
	}
	else if (circlePos.x < 20)
	{
		circleSpeed = 400.f;
	}

	circle.move(circleSpeed * dt, 0);
	
	// Stop the rectangle if out of window bounds
	if (input->isKeyDown(sf::Keyboard::W) && rectPos.y <= 0)
	{
		input->setKeyUp(sf::Keyboard::W);
	}
	else if (input->isKeyDown(sf::Keyboard::S) && rectPos.y >= (pos.y - 30))
	{
		input->setKeyUp(sf::Keyboard::S);
	}
	else if (input->isKeyDown(sf::Keyboard::A) && rectPos.x <= 0 )
	{
		input->setKeyUp(sf::Keyboard::A);
	}
	else if (input->isKeyDown(sf::Keyboard::D) && rectPos.x >= (pos.x - 30))
	{
		input->setKeyUp(sf::Keyboard::D);
	}

	// move circle2
	circle2.move(circle2SpeedX * dt, circle2SpeedY * dt);

	// -- CIRCLE2 DIRECTION CHANGES --

	// if circle2 hits right side of screen
	if (circle2Pos.x > (pos.x - 50))
	{
		circle2SpeedX = -circle2SpeedX;
		circle2.setPosition(pos.x - 50, circle2.getPosition().y);
	}

	// if circle2 hits left side of screen
	else if (circle2Pos.x < 0)
	{
		circle2SpeedX = -circle2SpeedX;
		circle2.setPosition(0, circle2.getPosition().y);
	}

	// if circle2 hits bottom of screen
	else if (circle2Pos.y > (pos.y - 50))
	{
		circle2SpeedY = -circle2SpeedY;
		circle2.setPosition(circle2.getPosition().x, pos.y - 50);
	}

	// if circle2 hits top of screen
	else if(circle2Pos.y < 0)
	{
		circle2SpeedY = -circle2SpeedY;
		circle2.setPosition(circle2.getPosition().x, 0);
	}
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(rect);
	window->draw(circle2);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}