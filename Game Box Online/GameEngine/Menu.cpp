//
//  Menu.cpp
//  Game Box Online
//
//  Created by Amy on 2018-09-14.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "Menu.hpp"
#include "../ResourcePath.hpp"
#include <string>
#include <iostream>
using namespace GameEngine;

sf::RectangleShape* screen;
sf::RectangleShape* rectangle;
sf::RectangleShape* play;
sf::Text* playText;
sf::Font* font;



Menu::Menu(sf::RenderTarget* target, sf::RenderWindow* window) :
m_target(target), m_window(window)
{
    font = new sf::Font();
    std::string filePath = resourcePath();
    filePath.append("sansation.ttf");
    if (!font->loadFromFile(filePath))
    {
        std::cout << "Can't find the font file" << std::endl;
    }

    filePath = resourcePath();
    filePath.append("SplashScreen.png");
    texture = new sf::Texture();
    texture->loadFromFile(filePath);
    screen = new sf::RectangleShape(sf::Vector2f(GameEngineMain::WINDOW_WIDTH, GameEngineMain::WINDOW_HEIGHT));
    
    screen->setTexture(texture);
    rectangle = new sf::RectangleShape(sf::Vector2f(120, 50));
    play = new sf::RectangleShape(sf::Vector2f(120, 50));
    rectangle->setPosition(100.f, 400.f);
    play->setPosition(300.f, 400.f);
    play->setFillColor(sf::Color::Blue);

    playText = new sf::Text;
    playText->setFont(*font);
    playText->setStyle(sf::Text::Bold);
    playText->setString( "Play Game" );
    playText->setCharacterSize(20);
    playText->setFillColor(sf::Color::White);
    playText->setPosition(310.f, 410.f);
   /* //Setup clickable regions
    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top= 145;
    playButton.rect.width = 100;
    playButton.rect.left = 0;
    playButton.rect.height = 50;
    playButton.action = Play; */
    
    
    
    
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
        m_window->draw(*rectangle);
        m_window->draw(*play);
        m_window->draw(*playText);
        
        
        // End the current frame and display its contents on screen
        m_window->display();
    }
    
    delete screen;
    delete rectangle;
    delete play;
    delete playText;
    delete texture;
    delete font;
}
