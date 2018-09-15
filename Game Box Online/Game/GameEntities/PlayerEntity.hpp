#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/PlayerMovementComponent.hpp"

namespace Game
{
  
  class PlayerEntity : public GameEngine::Entity
  {
  public:
    PlayerEntity();
    ~PlayerEntity();
    
    virtual void OnAddToWorld() override;
    virtual void OnRemoveFromWorld() override;
    
  protected:
    GameEngine::SpriteRenderComponent* m_renderComponent;
    PlayerMovementComponent*   m_playerMovementComponent;
    GameEngine::AnimationComponent* m_animComponent;
  };
}

