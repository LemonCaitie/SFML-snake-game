//include statements for all header files and SFML libraries.
#include "Background.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Background::Background() {
	// Get wall texture from file and set repeat to true.
	tileTex.loadFromFile(".\\assets\\textures\\wall.png");
	tileTex.setRepeated(true);

	//Set the texture and position of all the walls.
	bottom.setTexture(tileTex);
	bottom.setTextureRect(sf::IntRect(0, 0, 800, 50));
	bottom.setPosition(0, 650);

	top.setTexture(tileTex);
	top.setTextureRect(sf::IntRect(0, 0, 800, 50));
	top.setPosition(0, 0);

	left.setTexture(tileTex);
	left.setTextureRect(sf::IntRect(0, 0, 50, 800));
	left.setPosition(0, 0);

	right.setTexture(tileTex);
	right.setTextureRect(sf::IntRect(0, 0, 50, 800));
	right.setPosition(650, 0);
}

void Background::showBackground(sf::RenderWindow& window) {
	//Draw all of the walls. 
	window.draw(bottom);
	window.draw(top);
	window.draw(left);
	window.draw(right);
}
