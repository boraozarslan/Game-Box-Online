//
//  HealthStatusComponent.hpp
//  Game Box Online
//
//  Created by Amy on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//
#pragma once

#include "GameEngine/EntitySystem/Component.hpp"
#include "PlayerEntity.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace Game {
    class HealthStatusComponent : public GameEngine::Component
    {
    public:
        static std::vector<HealthStatusComponent*> healths;
        HealthStatusComponent();
        ~HealthStatusComponent();
        
        virtual void Update() override;
        virtual void OnAddToWorld() override;
        
        sf::Vector2f HealthPos;
        PlayerEntity* m_player;
    private:
    };
}


