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

enum Menu::MenuResult Menu::ShowMenu()
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
    
  // Play Button
  
  sf::RectangleShape play(sf::Vector2f(buttonWidth, buttonHeight));
  
  play.setPosition((GameEngineMain::WINDOW_WIDTH)*.20, (GameEngineMain::WINDOW_HEIGHT)*.7);
  play.setFillColor(sf::Color::Blue);
  
  sf::Text playText;
  playText.setFont(font);
  playText.setStyle(1);
  playText.setString( "Play Game" );
  playText.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
  playText.setFillColor(sf::Color::White);
  playText.setPosition((GameEngineMain::WINDOW_WIDTH)*.20, (GameEngineMain::WINDOW_HEIGHT)*.7);
    
    // Online Multiplayer Button
    
    sf::RectangleShape online(sf::Vector2f(buttonWidth*1.7, buttonHeight));
    online.setPosition((GameEngineMain::WINDOW_WIDTH)*.40, (GameEngineMain::WINDOW_HEIGHT)*.7);
    online.setFillColor(sf::Color::Blue);
    sf::Text onlineText;
    onlineText.setFont(font);
    onlineText.setStyle(1);
    onlineText.setString( "Online Multiplayer" );
    onlineText.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
    onlineText.setFillColor(sf::Color::White);
    onlineText.setPosition((GameEngineMain::WINDOW_WIDTH)*.40, (GameEngineMain::WINDOW_HEIGHT)*.7);
    
    
  // Exit Button
  
  sf::RectangleShape exitgame(sf::Vector2f(buttonWidth, buttonHeight));
  exitgame.setPosition((GameEngineMain::WINDOW_WIDTH)*.75,(GameEngineMain::WINDOW_HEIGHT)*.7);
  exitgame.setFillColor(sf::Color::Blue);
  
  sf::Text exitText;
  exitText.setFont(font);
  exitText.setStyle(sf::Text::Bold);
  exitText.setString( "Exit" );
  exitText.setCharacterSize((GameEngineMain::WINDOW_WIDTH)/42);
  exitText.setFillColor(sf::Color::White);
  exitText.setPosition((GameEngineMain::WINDOW_WIDTH)*.75,(GameEngineMain::WINDOW_HEIGHT)*.7);
  
  
    bool done = false;
    while (m_window->isOpen())
    {
        // get the bounding boxes of the entities
        sf::FloatRect boundingBoxPlay = play.getGlobalBounds();
        sf::FloatRect boundingBoxOnline = online.getGlobalBounds();
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
                    return Exit;
                 //  exit(0);
                }
            }
            
            // Request for closing the window
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            
            if (boundingBoxPlay.contains(Mouse))
            {
                // collision!
                //std::cout << "COLLISION!" << std::endl;
                
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    return Play;
                }
            }
            if (boundingBoxOnline.contains(Mouse))
            {
                // collision!
                
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    return Online;
                }
            }
            
            
        }
      
        // Clear the whole window before rendering a new frame
        m_window->clear();
        
        // Draw some graphical entities
      
      
        m_window->draw(screen);
        m_window->draw(play);
        m_window->draw(online);
        m_window->draw(exitgame);
        m_window->draw(playText);
        m_window->draw(onlineText);
        m_window->draw(exitText);
        
        // End the current frame and display its contents on screen
        m_window->display();
    }
    
    return Nothing;
}
