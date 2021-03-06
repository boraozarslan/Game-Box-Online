		//
//  SplashScreen.hpp
//  Game Box Online
//
//  Created by Amy on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "GameEngineMain.hpp"

namespace GameEngine
{
    class SplashScreen
    {
    public:
        SplashScreen(sf::RenderTarget* target, sf::RenderWindow* window);
        
        void WaitForKeystroke();
    private:
        sf::RenderTarget* m_target;
        sf::RenderWindow* m_window;
        sf::RectangleShape* screen;
        sf::Texture* texture;
    };
}
