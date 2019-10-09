#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
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
vector<Brick> Bricks(31, Brick(brick)); //create a vector(list) of bricks

sf::Font font; //Font for text

sf::Text livesText; //To display lives
sf::Text scoreText; //To display score
sf::Text endGame; //"Game Over"
sf::Text closeGame; //"To close window"

bool gameOver = false; //When lives run out

bool Game::Start() //Setting up the game
{
	sf::VideoMode vMode(windowWidth, windowHeight); //Videomode X, Y 
	window.setFramerateLimit(60); //Set framerate limit
	window.create(vMode, "Breakout"); //Create window

	font.loadFromFile("arial.ttf"); //Loading in font for text

	//Setup Bricks
	for (int i = 0; i < 31; i++)
	{
		Bricks[i].brickShape.setSize(brick.brickSize);
		Bricks[i].brickShape.setFillColor(sf::Color(rand() % 255 + 50, rand() % 255 + 50, rand() % 255 + 50));

		if (i <= 10)
		{
			Bricks[i].brickShape.setPosition(100 * i, 0);
		}
		else if (i > 20)
		{
			Bricks[i].brickShape.setPosition(100 * (i - 21), 100);
		}
		else if (i > 10)
		{
			Bricks[i].brickShape.setPosition(100 * (i - 11), 50);
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
	//Paddle Setup
	Paddle paddle;
	paddle.paddleShape.setSize(paddle.paddleSize);
	paddle.paddleShape.setFillColor(paddle.paddleColour);
	paddle.paddleShape.setPosition(windowWidth / 2, windowHeight - (windowHeight / 5));

	//Ball Setup
	Ball ball;
	ball.ballShape.setRadius(ball.ballRadius);
	ball.ballShape.setPosition(paddle.paddleShape.getPosition().x, paddle.paddleShape.getPosition().y - 75);
	ball.ballShape.setFillColor(ball.ballColour);

	ball.ballVelocity.x = 0.3;
	ball.ballVelocity.y = 0.5;

	//Code runs while window is open
	while (window.isOpen())
	{
		//Paddle movement based on mouse position
		if (sf::Mouse::getPosition(window).x > paddle.paddleShape.getSize().x / 2 && 
			sf::Mouse::getPosition(window).x < (window.getSize().x - paddle.paddleShape.getSize().x / 2))
		{
			paddle.paddleShape.setPosition(sf::Mouse::getPosition(window).x - paddle.paddleShape.getSize().x / 2, 
				paddle.paddleShape.getPosition().y);
		}

		//Ball and Border Collision
		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}
		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
			lives--;
			if (lives <= 0)
			{
				//End Game
				gameOver = true; //Change to gameover state
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
				score ++;
				ball.ballVelocity = ball.ballVelocity * 1.03f; //increasing speed of ball
			}
		}

		ball.ballShape.move(ball.ballVelocity); //Moves the ball

		string livesString;
		string scoreString;
		//Used to change int - string to display on screen
		livesString = to_string(lives);
		scoreString = to_string(score);

		//Lives setup
		livesText.setString("Lives: " + (livesString));
		livesText.setPosition(sf::Vector2f(30, 500));
		livesText.setFillColor(sf::Color::White);
		livesText.setCharacterSize(30);
		livesText.setFont(font);

		//Score setup
		scoreText.setString("Score: " + (scoreString));
		scoreText.setPosition(sf::Vector2f(860, 500));
		scoreText.setFillColor(sf::Color::White);
		scoreText.setCharacterSize(30);
		scoreText.setFont(font);

		//Game Over setup
		endGame.setFont(font);
		endGame.setCharacterSize(50);
		endGame.setFillColor(sf::Color::White);
		endGame.setString("GAME OVER");
		endGame.setPosition(350, 200);

		//To close window setup
		closeGame.setFont(font);
		closeGame.setCharacterSize(20);
		closeGame.setFillColor(sf::Color::White);
		closeGame.setString("Press SPACE to close window");
		closeGame.setPosition(370, 500);

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
		window.draw(livesText);
		window.draw(scoreText);

		//When game over is true
		if (gameOver == true)
		{
			window.clear(); //Clear to only display next "draw"
			scoreText.setPosition(sf::Vector2f(450, 270)); //Change pos for neater display
			
			//Stop the ball - the score will continue to update otherwise
			ball.ballVelocity.x = 0;
			ball.ballVelocity.y = 0;

			//Draw text
			window.draw(endGame);
			window.draw(scoreText);
			window.draw(closeGame);

			//Press space to close window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				return 1;
			}
		}
		window.display();
	}

	return 0;
}