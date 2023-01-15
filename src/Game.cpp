/*
CTEC1908 Deliverable 2 
Caitlin Doleman
P2653943
Date submitted: 05/05/2022
References: 
En.sfml-dev.org. 2021. What is wrong with this code?. [online] Available at: <https://en.sfml-dev.org/forums/index.php?topic=28331.0> [Accessed 25 April 2022].
Stack Overflow. 2022. Passing a std::vector<sf::RectangleShape> Array in SFML. [online] Available at: <https://stackoverflow.com/questions/35383652/passing-a-stdvectorsfrectangleshape-array-in-sfml> [Accessed 30 April 2022].
Dutta, A., 2022. C++ push_back | How push_back Method Works in C++? (Examples). [online] EDUCBA. Available at: <https://www.educba.com/c-plus-plus-push_back/> [Accessed 30 April 2022].
Beepbox.co. n.d. BeepBox. [online] Available at: <https://www.beepbox.co/#9n31s0k0l00e00t2ma7g0fj07r1i0o432T5v1ud1f0q0x10p71d23HXzzrrrqiii9998h0E1baT5v1ud3f10m8q011d23HVxh90000000000h0E0T1v1u93f10l7q8121d35A8F4B0Qd007P5aa3E1639T2v1u15f10w4qw02d03w0E0b4h400000000h4g000000014h000000008h4g0000000p1f0000kSKgf5SMubw> [Accessed 3 May 2022].
de Arteaga, P., n.d. Video Game Music by Patrick de Arteaga. [online] Patrickdearteaga.com. Available at: <https://patrickdearteaga.com/arcade-music/> [Accessed 2 May 2022].
*/



//include statements for all header files and SFML libraries.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "food.h"
#include "Square.h"
#include "Snake.h"
#include "Background.h"
#include "Score.h"

using namespace std;

int main()
{
    Snake snake({ 50,50 }); //Create instance of Snake.

    Background background; //Create instance of Background.
    Food food; //Create instance of Food.
    Score score; //Create instance of Score.

    bool hitWall = false; //Variable for if the snake has hit the wall.
    bool hitSnake = false; //Variable for if the snake has hit itself.
    bool eaten = false; //Variable for if the snake has hit food.
    bool win = false; //Has the player won?
    bool lose = false; //Has the player lost?
    sf::Vector2f direction = { 50.f,0.f }; //Starting direction for the snake to move, so it doesn't imediately hit it's body.

    sf::RenderWindow window(sf::VideoMode(700, 700), "Snake!"); //Create window for game.
    window.setFramerateLimit(60); //Set the max number of frames for second.

    sf::Clock timer; //Create timer so the snakes movement can be slowed down.

    //Set up background music to play repeatedly throughout the game.
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile(".\\assets\\audio\\InterstellarOdyssey.ogg")) return 0;
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30);
    backgroundMusic.play();

    while (window.isOpen())
    {
        //Check user events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //If the window has been closed.
                window.close();
        }

        //Changes the direction of the snake using the arrow keys.
        if (event.type == sf::Event::KeyPressed) {
            if ((!hitWall || !hitSnake) && event.key.code == sf::Keyboard::Up) {
                direction = { 0.f,-50.f };
            }
            if ((!hitWall || !hitSnake) && event.key.code == sf::Keyboard::Down) {
                direction = { 0.f,50.f };
            }
            if ((!hitWall || !hitSnake) && event.key.code == sf::Keyboard::Left) {
                direction = { -50.f,0.f };
            }
            if ((!hitWall || !hitSnake) && event.key.code == sf::Keyboard::Right) {
                direction = { 50.f,0.f };
            }
        }

        //Checks to see if the player has restarted the game.
        if ((win || lose) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //Resets the game variables so the player can play again.
            win = false;
            lose = false;
            direction = { 50.f,-0.f };
            score.resetScore();
            snake.setBody();
            food.destroyFood();
            timer.restart();
        }
    

        sf::Time elapsedTime = timer.getElapsedTime(); //How long has passed?

        if (elapsedTime.asSeconds() > 0.25f && !win && !lose) { //If the time has passed and the player hasn't won or lost yet...
            snake.moveSnake(direction); //Move the snake in the right direction.
            timer.restart(); //Restart the timer for player movement.
        }

        hitWall = snake.hitWall(); //Find out if that move made the snake hit a wall.
        hitSnake = snake.hitSnake(); //Find out if that move made the snake hit itself.
        if (hitWall || hitSnake) { //If it hit a wall or itself...
            lose = true; //The player loses.
        }

        eaten = snake.eatFood(food); //Find out if that move made the snake hit food.
        if (eaten) { //If the snake did hit food...
            food.destroyFood(); //Move the food to a new position.
            score.addToScore(); //Add one to the score.
            snake.increaseLength(); //Add a square to the snake.
        }

        window.clear(); 

        //Show all the elements to the game.
        background.showBackground(window);
        snake.showSnake(window);
        food.showFood(window);
        score.showScore(window);

        win = score.checkWin(); //Chech if the player has eaten 5 pieces of food.
        if (win) { //If the player has won...
            score.showGameEnd(window, "You win!"); //Show win statement.
        }
        else if (lose) {//If the player has lost...
            score.showGameEnd(window, "You Lose!"); //Show lose statement.
        }

        window.display(); //Update the window for player. 
    }

    return 0;
}
