//
//  Arkanoid
//
//  Created by Martin Pettersson on 15/10/15.
//
#include <stdio.h>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowHeight{600}, windowWidth{800};
constexpr float ballRadius{10.f}, ballVelocity{11.f};
constexpr float paddleWidth{100.f}, paddleHeight{10.f}, paddleVelocity{9.f};
constexpr float blockWidth{60.f}, blockHeight{20.f};
constexpr int countBlocksX{11}, countBlocksY{4};

struct Brick
{
    RectangleShape shape;
    bool destroyed{false};
    int health = 2;
    
    Brick(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({blockWidth, blockHeight});
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
        updateColor();
    }
    
    void updateColor()
    {
        int red = rand() % 255;
        int green = rand() % 255;
        int blue = rand() % 255;
        sf::Color color{static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue)};
        shape.setFillColor(color);
    }
    
    float x()       {return shape.getPosition().x;}
    float y()       {return shape.getPosition().y;}
    float left()    {return x() - shape.getSize().x / 2.f;}
    float right()   {return x() + shape.getSize().x / 2.f;}
    float top()     {return y() - shape.getSize().y / 2.f;}
    float bottom()  {return y() + shape.getSize().y / 2.f;}
};

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
    
    float x()       {return shape.getPosition().x;}
    float y()       {return shape.getPosition().y;}
    float left()    {return x() - shape.getSize().x / 2.f;}
    float right()   {return x() + shape.getSize().x / 2.f;}
    float top()     {return y() - shape.getSize().y / 2.f;}
    float bottom()  {return y() + shape.getSize().y / 2.f;}
};

template<class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right()
        && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
    if(!isIntersecting(mPaddle, mBall)) return;
    mBall.velocity.y = -ballVelocity;
    if(mBall.x() < mPaddle.x())
        mBall.velocity.x = -ballVelocity;
    else
        mBall.velocity.x = ballVelocity;
}

void testCollision(Brick &mBrick, Ball &mBall)
{
    if (!isIntersecting(mBrick, mBall))
        return;
    
    mBrick.destroyed = true;
    
    float overlapLeft   {mBall.right() - mBall.left()};
    float overlapRight  {mBall.right() - mBall.left()};
    float overlapTop    {mBall.bottom() - mBall.top()};
    float overlapBottom {mBall.bottom() - mBall.top()};
    
    bool ballFromLeft{fabs(overlapLeft) < fabs(overlapRight)};
    bool ballFromTop{fabs(overlapTop) < fabs( overlapBottom)};
    
    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverLapY{ballFromTop ? overlapTop : overlapBottom};
    
    if (fabs(minOverlapX) < fabs(minOverLapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
    
}

int main()
{
    Ball ball{windowWidth / 2, windowHeight / 2};
    Paddle paddle{windowWidth / 2, windowHeight - 50};
    vector<Brick> bricks;
    for (int iX{0}; iX < countBlocksX; ++iX)
        for (int iY{0}; iY < countBlocksY; ++iY)
            bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
    RenderWindow window{{windowWidth,windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);
    while (true) {
        window.clear(Color::Black);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape) || bricks.empty())
            break;
        testCollision(paddle, ball);
        ball.update();
        paddle.update();
        window.draw(paddle.shape);
        
        for (auto& brick : bricks) {
            testCollision(brick, ball);
        }
        bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick){return mBrick.destroyed;}), end(bricks));
        
        
        window.draw(ball.shape);
        for (auto& brick : bricks) window.draw(brick.shape);
        window.display();
        Event event;
        window.pollEvent(event);
    }
    return 0;
}
