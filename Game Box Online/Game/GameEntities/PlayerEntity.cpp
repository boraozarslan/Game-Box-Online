#include "PlayerEntity.hpp"

#include "../../GameEngine/EntitySystem/Components/CollidablePhysicsComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/ParticleEmitterComponent.hpp"

using namespace Game;

PlayerEntity::PlayerEntity()
{
  m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
  m_playerMovementComponent = static_cast<Game::PlayerMovementComponent*>(AddComponent<Game::PlayerMovementComponent>());
  AddComponent<GameEngine::CollidablePhysicsComponent>();
  m_renderComponent->SetTexture(GameEngine::eTexture::Player);
  m_renderComponent->SetZLevel(2);
  m_animComponent = static_cast<GameEngine::AnimationComponent*>(AddComponent<GameEngine::AnimationComponent>());
  AddComponent<GameEngine::ParticleEmitterComponent>();
}


PlayerEntity::~PlayerEntity()
{
  
}


void PlayerEntity::OnAddToWorld()
{
  GameEngine::Entity::OnAddToWorld();
  
  if (m_animComponent)
  {
    m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
  }
}


void PlayerEntity::OnRemoveFromWorld()
{
  GameEngine::Entity::OnRemoveFromWorld();
}
