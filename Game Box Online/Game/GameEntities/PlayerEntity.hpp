#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/PlayerMovementComponent.hpp"
#include "../GameComponents/PlayerCameraComponent.hpp"
#include "ProjectileEmitterComponent.hpp"

namespace Game
{
  
  class PlayerEntity : public GameEngine::Entity
  {
  public:
    PlayerEntity(bool isEnemy);
    ~PlayerEntity();
    
    virtual void OnAddToWorld() override;
    virtual void OnRemoveFromWorld() override;
    
    bool TakeDamage(float damage);
    void IncreaseScore(int score);
    int GetScore();
    bool IsAlive() {
        return m_health > 0;
    }
  protected:
    GameEngine::SpriteRenderComponent* m_renderComponent;
    PlayerMovementComponent*   m_playerMovementComponent;
    GameEngine::AnimationComponent* m_animComponent;
    PlayerCameraComponent* m_camera;
    float m_health;
    bool m_isEnemy;
    int m_score;
  };
}
