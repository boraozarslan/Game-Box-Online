#pragma once
#include "../Component.hpp"

#include "../Entity.hpp"
#include "../../GameEngineMain.hpp"

namespace GameEngine
{
  class ParticleComponent : public Component
  {
  public:
    ParticleComponent();
    virtual ~ParticleComponent();
    
    virtual void OnAddToWorld() override;
    virtual void OnRemoveFromWorld() override;
    
  protected:
    virtual void Update() override;
    
    float m_lifeTimer;
  };
}

