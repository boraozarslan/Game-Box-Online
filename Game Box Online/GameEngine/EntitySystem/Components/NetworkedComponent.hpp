//
//  NetworkedComponent.hpp
//  Game Box Online
//
//  Created by Bora Ozarslan on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once

#include "GameEngine/EntitySystem/Component.hpp"

namespace GameEngine
{
    //This one allows for movement and obstacle detection,
    class NetworkedComponent : public Component
    {
    public:
        NetworkedComponent();
        virtual ~NetworkedComponent();
        
        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;
        
        virtual void Update() override;
        
    private:
    };
}

