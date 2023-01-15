//include statements for all header files and SFML libraries.
#include "Score.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Score::Score() {
	scoreNo = 0; //Set score number variable.
	scoreText = "Score:"; //Set basic score text.
	scoreText += to_string(scoreNo); //Add the score number to the score text.

	//Load font of the text.
	if (!font.loadFromFile(".\\assets\\fonts\\emulogic.ttf")) {
		cout << "Couldn't load from file" << endl;
	}
	//Set score counter colour, size and position in window. 
	text.setFont(font);
	text.setPosition({ 250.f,15.f });
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setString(scoreText);
}

void Score::addToScore() {
	scoreNo += 1; //Add 1 to the score.
	
}

void Score::resetScore() {
	scoreNo = 0; //Reset score to zero (So the game can be played again).
}

void Score::drawScore() {
	//Creates new text with updated score number.
	scoreText = "Score:";
	scoreText += to_string(scoreNo);
}

void Score::showScore(sf::RenderWindow& window) {
	drawScore(); //Updates score text with new score. 
	text.setString(scoreText);
	window.draw(text); //draws the new score.
}

bool Score::checkWin() {
	if (scoreNo == 5) { //If the player has eaten 5 pieces of food...
		return true;
	}
	else {
		return false;
	}
}

void Score::showGameEnd(sf::RenderWindow& window, string statement) {
	//Creates end text variables.
	sf::Text endText;
	sf::Text instructions;

	//set size, colour, position and text for the end game statement (changes depending if they win or lose - info sent from Game.cpp).
	endText.setFont(font);
	endText.setPosition({ 0.f,665.f });
	endText.setCharacterSize(20);
	endText.setFillColor(sf::Color::Black);
	endText.setString(statement + "To play again press space");
	window.draw(endText); //draws the end game statement.
}
