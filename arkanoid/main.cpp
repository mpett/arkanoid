//
//  p1.cpp
//  arkanoid
//
//  Created by Martin Pettersson on 15/10/15.
//
#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{800}, windowHeight{600};
constexpr float ballRadius{10.f};

// Class for the ball
struct Ball
{
    CircleShape shape;
    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }
};

// Main game loop
int main()
{
    Ball ball{windowWidth / 2, windowHeight / 2};
    // Creation of the game window
    RenderWindow window{{windowHeight,windowWidth}, "Arkanoid"};
    window.setFramerateLimit(60);
    
    while (true) {
        // Clear the window from old graphics
        window.clear();
        // Exit the loop if the player presses "Escape"
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            break;
        }
        Event event;
        window.pollEvent(event);
        window.draw(ball.shape);
        window.display();
    }
}


