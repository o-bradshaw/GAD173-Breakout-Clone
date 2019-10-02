#include <SFML/Graphics.hpp>
#include <iostream>
#include "Main.h"
using namespace std;

int main()
{
	Game myGame;

	if (!myGame.Start())
	{
		return EXIT_FAILURE;
	}
	return myGame.Update();
	return 0;
}

Brick brick; //Define a Brick object
vector<Brick> Bricks(15, Brick(brick)); //create a vector(list) of bricks

bool Game::Start() //Setting up the game
{
	sf::VideoMode vMode(windowWidth, windowHeight); //Videomode X, Y
	window.setFramerateLimit(60); //Set framerate limit
	window.create(vMode, "Breakout"); //Create window

	//Setup Bricks
	for (int i = 0; i < 15; i++)
	{
		Bricks[i].brickShape.setSize(sf::Vector2f(70, 30));
		Bricks[i].brickShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		if (i <= 5)
		{
			Bricks[i].brickShape.setPosition(75 * i, 0);
		}
		else if (i > 10)
		{
			Bricks[i].brickShape.setPosition(75 * (i - 11), 60);
		}
		else if (i > 5)
		{
			Bricks[i].brickShape.setPosition(75 * (i - 6), 10);
		}
	}

	//Setup window borders
	top.setSize(sf::Vector2f(windowWidth, 1));
	top.setPosition(0, 0);
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowWidth, 1));
	bottom.setPosition(sf::Vector2f(0, windowHeight - 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowHeight));
	left.setPosition(0, 0);
	left.setFillColor(sf::Color::Black);
	right.setSize(sf::Vector2f(1, windowHeight));
	right.setPosition(sf::Vector2f(windowWidth - 1, 0));
	right.setFillColor(sf::Color::Black);

	return true;
}

int Game::Update()
{
	Paddle paddle;
	paddle.paddleShape.setSize(sf::Vector2f(120.f, 15.f));
	paddle.paddleShape.setFillColor(sf::Color::Blue);
	paddle.paddleShape.setPosition(windowWidth / 2, windowHeight - (windowHeight / 5));

	Ball ball;
	ball.ballShape.setRadius(12.f);
	ball.ballShape.setPosition(paddle.paddleShape.getPosition().x, paddle.paddleShape.getPosition().y - 30);
	ball.ballShape.setFillColor(sf::Color::Red);

	ball.ballVelocity.x = 0.1;
	ball.ballVelocity.y = 0.1;

	//Code runs while window is open
	while (window.isOpen())
	{
		//Paddle movement based on mouse position
		if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < (window.getSize().x - paddle.paddleShape.getSize().x/2))
		{
			paddle.paddleShape.setPosition(sf::Mouse::getPosition(window).x - paddle.paddleShape.getSize().x/2, paddle.paddleShape.getPosition().y);
		}

		//Ball and Border Collision
		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}
		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
			lives -= 1;
			if (lives < 1)
			{
				//End Game
				return 1;
			}
		}
		if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1);
		}

		//Ball and Paddle Collision
		if (paddle.paddleShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}

		//Ball and brick collision
		for (int i = 0; i < Bricks.size(); i++)
		{
			if (Bricks[i].brickShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
			{
				ball.Bounce(0);
				Bricks[i].brickShape.setPosition(1200, 0);
				score += 1;
				ball.ballVelocity = ball.ballVelocity * 1.03f; //increasing speed of ball
			}
		}

		ball.ballShape.move(ball.ballVelocity); //Moves the ball

		

		sf::Event event;
		//Window Updating
		while (window.pollEvent(event))
		{
			//If window closes
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Clear window & re-draw images
		window.clear();
		for (int i = 0; i < Bricks.size(); i++)
		{
			window.draw(Bricks[i].brickShape);
		}
		window.draw(top);
		window.draw(bottom);
		window.draw(left);
		window.draw(right);
		window.draw(paddle.paddleShape);
		window.draw(ball.ballShape);
		window.display();
	}

	return 0;
}