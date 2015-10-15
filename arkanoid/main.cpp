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

constexpr int windowHeight{600}, windowWidth{800};
constexpr float ballRadius{10.f}, ballVelocity{8.f}, paddleVelocity{8.f};
constexpr float paddleWidth{100.f}, paddleHeight{20.f};

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
        else if (right() > windowWidth) velocity.x = -ballVelocity;
        if (top() < 0) velocity.y = ballVelocity;
        if (bottom() > windowHeight) velocity.y = -ballVelocity;
    }
    
    // Property methods
    float x()       {return shape.getPosition().x;}
    float y()       {return shape.getPosition().y;}
    float left()    {return x() - shape.getRadius();}
    float right()   {return x() + shape.getRadius();}
    float top()     {return y() - shape.getRadius();}
    float bottom()  {return y() + shape.getRadius();}
};

struct Paddle
{
    RectangleShape shape;
    Vector2f velocity;
    Paddle(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(Color::Green);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }
    
    void update()
    {
        shape.move(velocity);
        if(Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
            velocity.x = -paddleVelocity;
        else if(Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
            velocity.x = paddleVelocity;
        else velocity.x = 0;
    }
    // Property methods
    float x()       {return shape.getPosition().x;}
    float y()       {return shape.getPosition().y;}
    float left()    {return x() - shape.getSize().x / 2.f;}
    float right()   {return x() + shape.getSize().x / 2.f;}
    float top()     {return x() - shape.getSize().y / 2.f;}
    float bottom()  {return x() + shape.getSize().y / 2.f;}
};

// Main game loop
int main()
{
    Ball ball{windowWidth / 2, windowHeight / 2};
    Paddle paddle{windowWidth / 2, windowHeight - 50};
    // Creation of the game window
    RenderWindow window{{windowWidth,windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);
    
    while (true) {
        
        // Clear the window from old graphics
        window.clear(Color::Black);
        // Exit the loop if the player presses "Escape"
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            break;
        }
        ball.update();
        paddle.update();
        
        window.draw(paddle.shape);
        window.draw(ball.shape);
        
        window.display();
        Event event;
        window.pollEvent(event);
    }
    return 0;
}
