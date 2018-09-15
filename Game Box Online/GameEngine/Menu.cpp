//
//  Menu.cpp
//  Game Box Online
//
//  Created by Amy on 2018-09-14.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "Menu.hpp"
#include "../ResourcePath.hpp"
using namespace GameEngine;

sf::RectangleShape* screen;

Menu::Menu(sf::RenderTarget* target, sf::RenderWindow* window) :
m_target(target), m_window(window)
{
    std::string filePath = resourcePath();
    filePath.append("SplashScreen.png");
    texture = new sf::Texture();
    texture->loadFromFile(filePath);
    screen = new sf::RectangleShape(sf::Vector2f(GameEngineMain::WINDOW_WIDTH, GameEngineMain::WINDOW_HEIGHT));
    screen->setTexture(texture);
}

void Menu::ShowMenu()
{
    bool done = false;
    while (m_window->isOpen())
    {
        // Event processing
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                m_window->close();
            if(event.type == sf::Event::KeyPressed)
            {
                done = true;
                break;
            }
        }
        if(done)
            break;
        
        // Clear the whole window before rendering a new frame
        m_window->clear();
        
        // Draw some graphical entities
        m_window->draw(*screen);
        
        // End the current frame and display its contents on screen
        m_window->display();
    }
    
    delete screen;
    delete texture;
}
