//
//  Menu.hpp
//  Game Box Online
//
//  Created by Amy on 2018-09-14.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <list>
#include "GameEngineMain.hpp"

namespace GameEngine {
    class Menu
    {
    public:
        Menu(sf::RenderTarget* target, sf::RenderWindow* window);
        enum MenuResult { Nothing, Exit, Play };
        struct MenuItem
            {
            public:
                sf::Rect<int> rect;
                MenuResult action;
            };
        MenuResult Show(sf::RenderWindow& window);
        
        void ShowMenu();
    private:
        sf::RenderTarget* m_target;
        sf::RenderWindow* m_window;
      
        MenuResult GetMenuResponse(sf::RenderWindow& window);
        MenuResult HandleClick(int x, int y);
        std::list<MenuItem> _menuItems;
    };
}

