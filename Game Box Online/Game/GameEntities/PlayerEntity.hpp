#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/PlayerMovementComponent.hpp"
#include "../GameComponents/PlayerCameraComponent.hpp"
#include "ProjectileEmitterComponent.hpp"
#include "BombEmitterComponent.hpp"
#include "HealthStatusComponent.hpp"

namespace Game
{
    class HealthStatusComponent;
  class PlayerEntity : public GameEngine::Entity
  {
  public:
    PlayerEntity(bool isEnemy, bool isServer = false);
    ~PlayerEntity();
    
    virtual void OnAddToWorld() override;
    virtual void OnRemoveFromWorld() override;
    
    bool TakeDamage(float damage);
    void IncreaseScore(int score);
    int GetScore();
      
    float m_health;
      
    bool IsAlive() {
        return m_health > 0;
    }
  protected:
    GameEngine::SpriteRenderComponent* m_renderComponent;
    PlayerMovementComponent*   m_playerMovementComponent;
    GameEngine::AnimationComponent* m_animComponent;
    PlayerCameraComponent* m_camera;
    HealthStatusComponent* m_healthStatus;
    bool m_isEnemy;
    int m_score;
  };
}
