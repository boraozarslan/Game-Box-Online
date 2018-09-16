#include <math.h>

#include "DumbProjectileComponent.hpp"

using namespace GameEngine;

DumbProjectileComponent::DumbProjectileComponent()
: m_toEmitTimer(0.f)
, m_projSpeed(5.f)
, m_reloadTime(1.f)
{

}

DumbProjectileComponent::~DumbProjectileComponent()
{

}

void DumbProjectileComponent::Update()
{
    float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    m_toEmitTimer -= dt;

    if (m_toEmitTimer > 0.f) {
        return;
    }

    m_toEmitTimer = RandomFloatRange(m_reloadTime * RELOAD_MIN_PERCENT, m_reloadTime);
    EmitProjectile();
}

void DumbProjectileComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}


void DumbProjectileComponent::OnRemoveFromWorld()
{
    Component::OnAddToWorld();
}


void DumbProjectileComponent::EmitProjectile()
{
    sf::Vector2f emitPos = GetEntity()->GetPos();
    sf::Vector2f targetPos = GameEngine::GameEngineMain::GetInstance()->GetGameBoard()->GetPlayer()->GetPos();

    Game::ProjectileEntity* projectileEntity = new Game::ProjectileEntity();
    Game::ProjectileMovementComponent* projMoveComponent = static_cast<Game::ProjectileMovementComponent*>(projectileEntity->AddComponent<Game::ProjectileMovementComponent>());
    SpriteRenderComponent* render = static_cast<SpriteRenderComponent*>(projectileEntity->AddComponent<SpriteRenderComponent>());
    AnimationComponent* animComponent = static_cast<AnimationComponent*>(projectileEntity->AddComponent<AnimationComponent>());

    float xDiff = targetPos.x - emitPos.x;
    float yDiff = targetPos.y - emitPos.y;

    float magnitude = sqrt(xDiff*xDiff + yDiff*yDiff);
    sf::Vector2f direction = sf::Vector2f(xDiff * m_projSpeed / magnitude, yDiff * m_projSpeed / magnitude);

    projMoveComponent->SetVector(direction);
    projMoveComponent->SetDuration(2.f);

    render->SetTexture(GameEngine::eTexture::Particles);
    render->SetZLevel(1);

    projectileEntity->SetPos(emitPos);
    projectileEntity->SetSize(sf::Vector2f(40.f, 40.f));
    projectileEntity->SetSource(static_cast<Game::PlayerEntity*>(GetEntity()));

    GameEngine::GameEngineMain::GetInstance()->AddEntity(projectileEntity);
}
