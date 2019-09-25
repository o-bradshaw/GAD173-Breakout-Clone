#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
	int windowX = 600; //Window width
	int windowY = 600; //Window height
	int speed = 15; //Movement Speed
	int ballSize = 10; //Size of ball radius

	sf::Vector2f paddleSize = sf::Vector2f(100.f, 30.f); //Size of the shape
	sf::Vector2f paddlePos = sf::Vector2f((windowX / 2) - (paddleSize.x / 2), (windowY) - (paddleSize.y + 20)); //Bottom centre of window
	sf::Color colour = sf::Color(0,0,255,255); //0-255 rgba - Custom Colour

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Window"); //Created a render window
	window.setFramerateLimit(60);

	sf::RectangleShape paddle(paddleSize); //Create Paddle
	paddle.setFillColor(colour); //Set the colour
	paddle.setPosition(paddlePos); //Paddle spawn

	sf::CircleShape ball(ballSize); //Create Ball
	ball.setFillColor(sf::Color::White); //Set the colour
	sf::Vector2f ballPos = sf::Vector2f(paddlePos.x, paddlePos.y - paddleSize.y); //Set ball pos above paddle
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f); //Setup velocity
	velocity.x = rand() % 10; //Initial x will be random
	velocity.y = -5; //Ball starts heading towards top of window
	ball.setPosition(ballPos); //Ball spawn
	
	//Code runs while window is open
	while (window.isOpen())
	{
		//Check left button pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//Move left
			paddlePos.x -= speed;
			//Outside window left - come back
			if (paddlePos.x <= 0)
			{
				paddlePos.x = 0;
			}
			//Update the pos of paddle
			paddle.setPosition(paddlePos);

		}
		//Check right button pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//Move right
			paddlePos.x += speed;
			//Outside window right - come back
			if (paddlePos.x >= windowX - paddleSize.x)
			{
				paddlePos.x = windowX - paddleSize.x;
			}
			//Update the pos of paddle
			paddle.setPosition(paddlePos);
		}

		ball.move(velocity); //Constant movement of ball

		//Check ball position x - flip to remain within window
		if (ball.getPosition().x <= 0 || ball.getPosition().x >= (windowX-(ballSize*2)))
		{
			velocity.x = -velocity.x;
		}
		//Checks ball position y - flip to remain within window
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= (windowY-(ballSize*2)))
		{
			velocity.y = -velocity.y;
		}

		if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
		{
			velocity.y = -velocity.y;
		}

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

		window.clear();
		window.draw(paddle);
		window.draw(ball);
		window.display();
	}

	return 0;
}