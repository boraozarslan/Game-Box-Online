#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/PlayerMovementComponent.hpp"
#include "../GameComponents/PlayerCameraComponent.hpp"
#include "ProjectileEmitterComponent.hpp"
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
