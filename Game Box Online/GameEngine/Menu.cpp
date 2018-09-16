//
//  Menu.cpp
//  Game Box Online
//
//  Created by Amy on 2018-09-14.
//  Copyright © 2018 Gamebox. All rights reserved.
//h

#include "Menu.hpp"
#include "../ResourcePath.hpp"
#include <string>
#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace GameEngine;

Menu::Menu(sf::RenderTarget* target, sf::RenderWindow* window) :
m_target(target), m_window(window)
{
}

void Menu::ShowMenu()
{
  sf::Font font;
  std::string filePath = resourcePath();
  filePath.append("sansation.ttf");
  if (!font.loadFromFile(filePath))
  {
    std::cout << "Can't find the font file" << std::endl;
  }
  
  
  filePath = resourcePath();
  filePath.append("SplashScreen.png");
  sf::Texture texture;
  texture.loadFromFile(filePath);
  sf::RectangleShape screen(sf::Vector2f(GameEngineMain::WINDOW_WIDTH, GameEngineMain::WINDOW_HEIGHT));
  
  const int buttonWidth = (GameEngineMain::WINDOW_WIDTH) / 8;
  const int buttonHeight = (GameEngineMain::WINDOW_WIDTH) / 20;
  
  screen.setTexture(&texture);
  
  sf::RectangleShape play(sf::Vector2f(buttonWidth, buttonHeight));
  
  play.setPosition((GameEngineMain::WINDOW_WIDTH)*.30, (GameEngineMain::WINDOW_HEIGHT)*.7);
  play.setFillColor(sf::Color::Blue);
  
  sf::Text playText;
  playText.setFont(font);
  playText.setStyle(1);
  playText.setString( "Play Game" );
  playText.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
  playText.setFillColor(sf::Color::White);
  playText.setPosition((GameEngineMain::WINDOW_WIDTH)*.30, (GameEngineMain::WINDOW_HEIGHT)*.7);
  
  sf::RectangleShape exitgame(sf::Vector2f(buttonWidth, buttonHeight));
  exitgame.setPosition((GameEngineMain::WINDOW_WIDTH)*.60,(GameEngineMain::WINDOW_HEIGHT)*.7);
  exitgame.setFillColor(sf::Color::Blue);
  
  sf::Text exitText;
  exitText.setFont(font);
  exitText.setStyle(sf::Text::Bold);
  exitText.setString( "Exit" );
  exitText.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
  exitText.setFillColor(sf::Color::White);
  exitText.setPosition((GameEngineMain::WINDOW_WIDTH)*.60,(GameEngineMain::WINDOW_HEIGHT)*.7);
  
  
    bool done = false;
    while (m_window->isOpen())
    {
        // get the bounding box of the entities
        sf::FloatRect boundingBox = play.getGlobalBounds();
        sf::FloatRect boundingBoxExit = exitgame.getGlobalBounds();
        
        // Event processing
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            sf::Vector2f Mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
            if (boundingBoxExit.contains(Mouse))
            {
                // collision!
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    exit(0);
                }
            }
            // Request for closing the window
            if (event.type == sf::Event::Closed)
            {
                
                m_window->close();
            }
            
            if (boundingBox.contains(Mouse))
            {
                // collision!
                //std::cout << "COLLISION!" << std::endl;
                
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    done = true;
                    break;
                }
            }
        }
        if(done)
            break;
      
      
        // Clear the whole window before rendering a new frame
        m_window->clear();
        
        // Draw some graphical entities
      
      
        m_window->draw(screen);
        m_window->draw(play);
        m_window->draw(exitgame);
        m_window->draw(playText);
        m_window->draw(exitText);
        
        // End the current frame and display its contents on screen
        m_window->display();
    }
}
