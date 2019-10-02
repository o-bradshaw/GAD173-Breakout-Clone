#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Brick
{
public:
	sf::RectangleShape brickShape;
	sf::Color brickColour;
	sf::Vector2f brickSize;
	sf::Vector2f brickPos;
};

class Paddle
{
public:
	void UpdatePosition(float direction)
	{
		paddleShape.setPosition(direction * speed, paddleShape.getPosition().y);
	}
	float speed = 10.f;
	sf::RectangleShape paddleShape;
	sf::Color paddleColour;
	sf::Vector2f paddleSize;
	sf::Vector2f paddlePos;
};

class Ball 
{
public:
	void Bounce(int direction)
	{
		switch (direction)
		{
		case 0: //Vertical
			ballVelocity.y = -ballVelocity.y;
			break;
		case 1: //Horizontal
			ballVelocity.x = -ballVelocity.x;
			break;
		case 2: //Both
			ballVelocity.y = -ballVelocity.y;
			ballVelocity.x = -ballVelocity.x;
			break;
		}
	}
	sf::CircleShape ballShape;
	sf::Vector2f ballStartPos;
	sf::Vector2f ballVelocity;
	float ballRadius = 10.f;
};

class Game //Functions that run the game
{
public:
	bool Start();
	int Update();

private:
	sf::RenderWindow window;
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;
	float windowWidth = 600;
	float windowHeight = 600;
	int score = 0;
	int lives = 3;
};