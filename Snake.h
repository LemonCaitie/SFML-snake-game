#pragma once
//include statements for all header files and SFML libraries.
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "food.h"
#include "Background.h"

class Snake {
private:
	int bodyLength;
	sf::RectangleShape snake;
	std::vector<sf::RectangleShape> bodyparts;
	sf::Texture snakeFaceTex;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
	sf::Sound eatingSound;
	sf::Sound hitSound;
public:
	Snake(sf::Vector2f size);
	void setBody();
	void showSnake(sf::RenderWindow& window);
	void startPos(sf::Vector2f position);
	void increaseLength();
	void moveSnake(sf::Vector2f movement);
	bool hitWall();
	bool hitSnake();
	bool eatFood(Food food);
};
