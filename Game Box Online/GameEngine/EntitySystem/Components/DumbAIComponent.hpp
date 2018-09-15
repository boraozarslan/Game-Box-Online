//
//  DumbAIComponent.hpp
//  Game Box Online
//
//  Created by Ben Zhang on 2018-09-15.
//  Copyright © 2018 Gamebox. All rights reserved.
//

#pragma once
#include <stdio.h>

#include "GameEngine/EntitySystem/Component.hpp"

#include "GameEngine/EntitySystem/Entity.hpp"
#include "GameEngine/GameEngineMain.hpp"

namespace GameEngine
{
    class DumbAIComponent : public Component
    {
    public:
        DumbAIComponent();
        virtual ~DumbAIComponent();
        
        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;
        
    protected:
        virtual void Update() override;
    };
}
