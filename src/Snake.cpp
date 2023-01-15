//include statements for all header files and SFML libraries.
#include "Snake.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

Snake::Snake(sf::Vector2f size) {
	bodyLength = 3; //Starting snake body length.
	snake.setSize(size); //Set the snake's head size.
	snake.setFillColor(sf::Color::Green); //Set snake head to green (There as a backup for if texture for the head doesn't work).

	setBody(); //Create the snake's body.

	snakeFaceTex.loadFromFile(".\\assets\\textures\\snakeFace.png"); //Get image of snake face for texture.
	snake.setTexture(&snakeFaceTex); //Attach the face to the head rectangle (snake). 

	//Load sound files for sound effects.
	buffer.loadFromFile(".\\assets\\audio\\beep.flac");
	buffer2.loadFromFile(".\\assets\\audio\\BeepBox-Song.wav");

	//Set up eating sound.
	eatingSound.setBuffer(buffer);
	eatingSound.setRelativeToListener(true);
	eatingSound.setMinDistance(50.f);
	eatingSound.setPosition(snake.getPosition().x, 0.f, snake.getPosition().y);

	//Set up hit sound.
	hitSound.setBuffer(buffer2);
	hitSound.setVolume(90);
}


void Snake::showSnake(sf::RenderWindow& window) {
	for (int i = 0; i != bodyparts.size(); i++) { //For as many body parts as created...
		window.draw(bodyparts[i]); //Draw a new body part.
	}
	window.draw(snake); //Draw the snake's head.
}

void Snake::startPos(sf::Vector2f position) {
	snake.setPosition(position); //Set the head's position.
	for (int i = 0; i != bodyLength; i++) { //For each body part...
		position.x -= 50; //Move the width of a bodypart left.
		bodyparts[i].setPosition(position); //Set the position of the next body part there. 
	}
}

void Snake::setBody() {
	bodyLength = 3; //Reset body length.
	bodyparts.clear(); //Clear/get rid of the exisiting body parts (for if the player plays again).
	for (int i = 0; i != bodyLength; i++) { //For as made body parts as started with...
		bodyparts.push_back(sf::RectangleShape({ 50,50 })); //Create a new body part.
		bodyparts[i].setFillColor(sf::Color::Green); //Make the part green.
	}
	startPos({300,300}); //Move the snake to it's starting position.
}

void Snake::increaseLength() {
	bodyparts.push_back(sf::RectangleShape({ 50,50 })); //Add a new body part.
	bodyparts.back().setFillColor(sf::Color::Green);  //Make the part green.
	bodyparts.back().setPosition({-50,0}); //Position it at the end of the snake.
}

void Snake::moveSnake(sf::Vector2f movement) {
	sf::Vector2f nextPosition = snake.getPosition(); //store where the head was.
	sf::Vector2f lastPosition; //create variable for the body parts position.
	
	snake.move(movement); //Move the snake head.
	for (int i = 0; i != bodyparts.size(); i++) { //For each body part...
		lastPosition = bodyparts[i].getPosition(); //Store where the body part was.
		bodyparts[i].setPosition(nextPosition); //Move the body part to where the previous part of the snake was.
		nextPosition = lastPosition; //Store the old position as the the next parts new position. 
	}
}

bool Snake::hitWall() {

	Background background; //Create an instance of the background so GlobalBounds can be found of walls easily.

	//Add collision detection to the snake head and all the walls.
	sf::FloatRect snakeBoundBox = snake.getGlobalBounds();
	sf::FloatRect topBoundBox = background.top.getGlobalBounds();
	sf::FloatRect bottomBoundBox = background.bottom.getGlobalBounds();
	sf::FloatRect leftBoundBox = background.left.getGlobalBounds();
	sf::FloatRect rightBoundBox = background.right.getGlobalBounds();

	if (snakeBoundBox.intersects(leftBoundBox) || snakeBoundBox.intersects(rightBoundBox) || snakeBoundBox.intersects(topBoundBox) || snakeBoundBox.intersects(bottomBoundBox))  // When rectange hits any of the walls.
	{
		cout << "Snake hit the wall!" << endl; //Checking statement.
		hitSound.play(); 
		setBody(); //Reset the snake.
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::hitSnake() {
	for (int i = 0; i != bodyparts.size(); i++) { //For each body part.
		if (bodyparts[i].getGlobalBounds().intersects(snake.getGlobalBounds())) { //Check if the snake head hit that body part.
			cout << "Snake hit itself!" << endl; //Checking statement.
			hitSound.play();
			setBody(); //Reset the snake.
			return true;
		}
	}
	return false;
}

bool Snake::eatFood(Food food) {
	sf::FloatRect snakeBoundBox = snake.getGlobalBounds(); //Collision detection for the snake head.

	if (snakeBoundBox.intersects(food.getGlobalBounds())) {
		cout << "Food is eaten!" << endl;//Checking statement.
		eatingSound.play();
		return true;
	}
	else
	{
		return false;
	}
}
