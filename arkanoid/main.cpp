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

constexpr int windowHeight{800}, windowWidth{600};
constexpr float ballRadius{10.f}, ballVelocity{8.f};

// Class for the ball
struct Ball
{
    CircleShape shape;
    Vector2f velocity{-ballVelocity, -ballVelocity};
    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }
    void update()
    {
        shape.move(velocity);
        if(left() < 0) velocity.x = ballVelocity;
        else if (right() > windowHeight) velocity.x = -ballVelocity;
        
        if (top() < 0) velocity.y = ballVelocity;
        if (bottom() > windowWidth) velocity.y = -ballVelocity;
    }
    
    // Property methods
    float x()       {return shape.getPosition().x;}
    float y()       {return shape.getPosition().y;}
    float left()    {return x() - shape.getRadius();}
    float right()   {return x() + shape.getRadius();}
    float top()     {return y() - shape.getRadius();}
    float bottom()  {return y() + shape.getRadius();}
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
        ball.update();
        Event event;
        window.pollEvent(event);
        window.draw(ball.shape);
        window.display();
    }
}
