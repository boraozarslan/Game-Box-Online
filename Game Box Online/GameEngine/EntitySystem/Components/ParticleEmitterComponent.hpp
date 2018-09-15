#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../Component.hpp"

namespace GameEngine
{
  class ParticleEmitterComponent: public Component
  {
  public:
    ParticleEmitterComponent();
    virtual ~ParticleEmitterComponent();
    
    virtual void OnAddToWorld() override;
    virtual void OnRemoveFromWorld() override;
    
    virtual void Update() override;
  protected:
    void EmitParticle();
    
    //Placeholder temp - should go to helpers or smth.
    float RandomFloatRange(float a, float b)
    {
      return ((b - a) * ((float)rand() / RAND_MAX)) + a;
    }
    
    float m_toEmitTimer;
    float m_maxTimeToEmit;
    float m_minTimeToEmit;
  };
}

