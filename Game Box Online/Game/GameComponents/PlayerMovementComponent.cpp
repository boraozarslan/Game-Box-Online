#include "PlayerMovementComponent.hpp"

#include "../../GameEngine/GameEngineMain.hpp"

#include "../../GameEngine/Util/TextureManager.hpp"
#include "../../GameEngine/Util/AnimationManager.hpp"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
: m_flyTimerDt(0.f)
, m_flyTimerMaxTime(2.f)
, m_animComponent(nullptr)
{
  
}


PlayerMovementComponent::~PlayerMovementComponent()
{
  
}

void PlayerMovementComponent::OnAddToWorld()
{
  m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
}


void PlayerMovementComponent::Update()
{
  Component::Update();
  
  if (GameEngine::GameEngineMain::GetInstance()->IsGameOver())
  {
    return;
  }
  
  float dt = GameEngine::GameEngineMain::GetTimeDelta();
  static float playerVel = 150.f; //Pixels/s
  sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);
  bool wantsToFly = false;
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    wantedVel.x -= playerVel * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    wantedVel.x += playerVel * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    wantedVel.y -= playerVel * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    wantedVel.y += playerVel * dt;
  }
  
  GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);
  
  if (wantedVel != sf::Vector2f(0.f, 0.f))
  {
    m_flyTimerDt = m_flyTimerMaxTime;
  }
  else
  {
    m_flyTimerDt -= dt;
  }
  
  if (m_animComponent)
  {
    if (m_flyTimerDt > 0.f)
    {
      if (m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::BirdFly)
      {
        m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdFly);
      }
    }
    else if(m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::BirdIdle)
    {
      m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
    }
  }
  
  
  static float rotationVel = 50.f; //Deg/s
  static float maxRotation = 20.f; //Deg
  
  float currentRotation = GetEntity()->GetRot();
  float wantedRot = 0.f;
  bool  reseting = false;
  
  if (wantedVel.y > 0.f)
    wantedRot = rotationVel;
  else if (wantedVel.y < 0.f)
    wantedRot = -rotationVel;
  else
  {
    if (currentRotation > 0.f)
      wantedRot = -rotationVel;
    else if (currentRotation < 0.f)
      wantedRot = rotationVel;
  }
  
  float frameRot = wantedRot * dt;
  float totalRot = currentRotation + frameRot;
  
  if (!reseting)
  {
    if (totalRot > maxRotation)
      totalRot = maxRotation;
    else if (totalRot < -maxRotation)
      totalRot = -maxRotation;
  }
  else
  {
    if (currentRotation > 0.f && totalRot < 0.f)
      totalRot = 0.f;
    if (currentRotation < 0.f && totalRot > 0.f)
      totalRot = 0.f;
  }
  
  GetEntity()->SetRotation(totalRot);
}
