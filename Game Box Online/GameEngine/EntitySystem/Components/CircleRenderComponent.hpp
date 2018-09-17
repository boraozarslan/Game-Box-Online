//
//  CircleRenderComponent.hpp
//  Game Box Online
//
//  Created by Amy on 2018-09-16.
//  Copyright © 2018 Gamebox. All rights reserved.
//
#pragma once
#include "RenderComponent.hpp"

namespace GameEngine
{
    
    class CircleRenderComponent : public RenderComponent
    {
    public:
        
        virtual void Render(sf::RenderTarget* target) override;
        
        sf::CircleShape Circle;
    };
}
