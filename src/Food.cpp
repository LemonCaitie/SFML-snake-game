//include statements for all header files and SFML libraries.
#include "food.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>


Food::Food() {
	//Set up food shape, size and colour.
	food.setRadius(15.f);
	food.setFillColor(sf::Color::Cyan);

	generateFood(); //Randomly place the food.
}

void Food::generateFood() {
	//Randomly generate cordinates (srand so reach time the player plays the food doesn't follow a pattern).
	srand(time(0));
	float newPosX = (rand() % 11 + 1.2)*50;
	float newPosY = (rand() % 11 + 1.2)*50;
	food.setPosition(newPosX, newPosY); //Sets the food's new position.
}

void Food::destroyFood() {
	generateFood(); //Move the food to a new random position.
}

void Food::showFood(sf::RenderWindow& window) {
	window.draw(food); //draw the food.
}