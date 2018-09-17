//
//  CircleRenderComponent.cpp
//  Game Box Online
//
//  Created by Amy on 2018-09-16.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "CircleRenderComponent.hpp"

using namespace GameEngine;

void CircleRenderComponent::Render(sf::RenderTarget* target)
{
    RenderComponent::Render(target);
    SetZLevel(6);
    
    target->draw(Circle);
}
