#pragma once
//include statements for SFML library.
#include <SFML/Graphics.hpp>

using namespace std;
using std::to_string;

class Score {
private:
	sf::Font font;
	sf::Text text;
	int scoreNo;
	string scoreText;
	void drawScore();
public:
	Score();
	void addToScore();
	void resetScore();
	void showScore(sf::RenderWindow& window);
	bool checkWin();
	void showGameEnd(sf::RenderWindow& window, string statement);
};
