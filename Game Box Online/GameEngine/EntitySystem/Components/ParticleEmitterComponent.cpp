#include "ParticleEmitterComponent.hpp"

#include "ParticleComponent.hpp"
#include "SpriteRenderComponent.hpp"
#include "AnimationComponent.hpp"
#include "../Entity.hpp"
#include "../../GameEngineMain.hpp"

#include <SFML/System/Vector2.hpp>


using namespace GameEngine;

ParticleEmitterComponent::ParticleEmitterComponent()
: m_toEmitTimer(0.f)
, m_maxTimeToEmit(0.3f)
, m_minTimeToEmit(0.1f)
{
  
}


ParticleEmitterComponent::~ParticleEmitterComponent()
{
  
}


void ParticleEmitterComponent::Update()
{
  float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
  m_toEmitTimer -= dt;
  
  if (m_toEmitTimer <= 0.f)
  {
    EmitParticle();
    
    m_toEmitTimer = RandomFloatRange(m_minTimeToEmit, m_maxTimeToEmit);
  }
}

void ParticleEmitterComponent::OnAddToWorld()
{
  Component::OnAddToWorld();
}


void ParticleEmitterComponent::OnRemoveFromWorld()
{
  Component::OnAddToWorld();
}


void ParticleEmitterComponent::EmitParticle()
{
  sf::Vector2f emitPos = GetEntity()->GetPos();
  
  Entity* particleEntity = new Entity();
  SpriteRenderComponent* render = static_cast<SpriteRenderComponent*>(particleEntity->AddComponent<SpriteRenderComponent>());
  ParticleComponent* particleCMP = static_cast<ParticleComponent*>(particleEntity->AddComponent<ParticleComponent>());
  AnimationComponent* animComponent = static_cast<AnimationComponent*>(particleEntity->AddComponent<AnimationComponent>());
  
  render->SetTexture(eTexture::Particles);
  render->SetZLevel(1);
  
  particleEntity->SetPos(emitPos);
  particleEntity->SetSize(sf::Vector2f(32.f, 32.f));
  
  animComponent->PlayAnim(EAnimationId::Smoke);
  
  GameEngineMain::GetInstance()->AddEntity(particleEntity);
}
