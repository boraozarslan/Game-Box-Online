#pragma once
#include "../../GameEngine/EntitySystem/Component.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"

namespace Game
{
  class PlayerMovementComponent : public GameEngine::Component
  {
  public:
    PlayerMovementComponent();
    ~PlayerMovementComponent();
    
    virtual void Update() override;
    virtual void OnAddToWorld() override;
    
  private:
    float m_flyTimerDt;
    float m_flyTimerMaxTime;
    
    GameEngine::AnimationComponent* m_animComponent;
  };
}


