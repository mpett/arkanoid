//
//  p1.cpp
//  arkanoid
//
//  Created by Martin Pettersson on 15/10/15.
//  Copyright © 2015 Martin Pettersson. All rights reserved.
//
#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{800}, windowHeight{600};

int main()
{
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
        // Display the contents of the window
        window.display();
    }
}


