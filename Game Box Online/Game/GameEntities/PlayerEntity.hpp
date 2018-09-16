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
    PlayerEntity(bool isEnemy);
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
    GameEngine::SpriteRenderComponent* m_renderComponent = nullptr;
    PlayerMovementComponent*   m_playerMovementComponent = nullptr;
    GameEngine::AnimationComponent* m_animComponent = nullptr;
    PlayerCameraComponent* m_camera = nullptr;
    HealthStatusComponent* m_healthStatus = nullptr;
    bool m_isEnemy;
    int m_score;
  };
}
