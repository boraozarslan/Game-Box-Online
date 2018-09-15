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
sf::RectangleShape* exitgame;
sf::RectangleShape* play;
sf::Text* playText;
sf::Text* exitText;
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
    
    const int buttonWidth = (GameEngineMain::WINDOW_WIDTH) / 8;
    const int buttonHeight = (GameEngineMain::WINDOW_WIDTH) / 20;
    
    screen->setTexture(texture);
    
    play = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    
    play->setPosition((GameEngineMain::WINDOW_WIDTH)*.30, (GameEngineMain::WINDOW_HEIGHT)*.7);
    play->setFillColor(sf::Color::Blue);
    playText = new sf::Text;
    playText->setFont(*font);
    playText->setStyle(sf::Text::Bold);
    playText->setString( "Play Game" );
    playText->setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
    playText->setFillColor(sf::Color::White);
    playText->setPosition((GameEngineMain::WINDOW_WIDTH)*.30, (GameEngineMain::WINDOW_HEIGHT)*.7);
    
    exitgame = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    exitgame->setPosition((GameEngineMain::WINDOW_WIDTH)*.60,(GameEngineMain::WINDOW_HEIGHT)*.7);
    exitgame->setFillColor(sf::Color::Blue);
    exitText = new sf::Text;
    exitText->setFont(*font);
    exitText->setStyle(sf::Text::Bold);
    exitText->setString( "Exit" );
    exitText->setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
    exitText->setFillColor(sf::Color::White);
    exitText->setPosition((GameEngineMain::WINDOW_WIDTH)*.60,(GameEngineMain::WINDOW_HEIGHT)*.7);
    
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
            if(event.type == sf::Event::MouseButtonPressed)
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
        m_window->draw(*play);
        m_window->draw(*playText);
        m_window->draw(*exitgame);
        m_window->draw(*exitText);
        
        // End the current frame and display its contents on screen
        m_window->display();
    }
  
    delete playText;
    delete screen;
    delete play;
<<<<<<< HEAD
    delete exitgame;
    delete playText;
    delete exitText;
    delete texture;
=======
>>>>>>> 09c5af88f5bc54908974927b7beb0039129d57bd
    delete font;
    delete texture;
}
