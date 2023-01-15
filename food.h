#pragma once
//include statements for SFML library.
#include <SFML/Graphics.hpp>

class Food {
private:
	sf::CircleShape food;
public:
	Food();
	void generateFood();
	void destroyFood();
	void showFood(sf::RenderWindow& window);

	sf::FloatRect getGlobalBounds() {
		return food.getGlobalBounds();
	}
};
