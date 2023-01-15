#pragma once
//include statements for all header files and SFML libraries.
#include "Snake.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Background {
private: 
	sf::Texture tileTex;
public:
	sf::Sprite top, bottom, left, right;
	Background();
	void showBackground(sf::RenderWindow& window);
};
