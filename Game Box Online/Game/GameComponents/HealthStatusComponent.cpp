//
//  HealthStatusComponent.cpp
//  Game Box Online
//
//  Created by Amy on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#include "HealthStatusComponent.hpp"
#include "GameEngine/GameEngineMain.hpp"
#include <algorithm>

using namespace Game;

std::vector<HealthStatusComponent*> HealthStatusComponent::healths;

HealthStatusComponent::HealthStatusComponent() : m_player(nullptr)
{
    healths.push_back(this);
}

HealthStatusComponent::~HealthStatusComponent()
{
    healths.erase(std::remove(healths.begin(), healths.end(), this), healths.end());
}

void HealthStatusComponent::Update()
{
    if(m_player == nullptr)
        m_player = static_cast<PlayerEntity*>(GetEntity());
    Component::Update();
    
    auto pos = GetEntity()->GetPos();
    
    HealthPos = pos + sf::Vector2f(100.f, 100.f);
}

void HealthStatusComponent::OnAddToWorld()
{
    
}
