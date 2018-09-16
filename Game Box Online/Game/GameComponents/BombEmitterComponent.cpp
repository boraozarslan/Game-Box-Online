#include "BombEmitterComponent.hpp"
#include <math.h>
#include <iostream>

using namespace Game;

BombEmitterComponent::BombEmitterComponent()
: m_cooldownRemaining(0.f)
, m_reloadTime(5.f)
{

}

BombEmitterComponent::~BombEmitterComponent()
{

}

void BombEmitterComponent::Update()
{
    float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    m_cooldownRemaining = fmax(m_cooldownRemaining - dt, 0.f);

    if (m_cooldownRemaining > 0.f || GameEngine::GameEngineMain::GetInstance()->IsGameOver()) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // fire here
        FireBomb();
        m_cooldownRemaining = m_reloadTime;
    }
}

void BombEmitterComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}


void BombEmitterComponent::OnRemoveFromWorld()
{
    Component::OnRemoveFromWorld();
}


void BombEmitterComponent::FireBomb()
{
    auto gameInstance = GameEngine::GameEngineMain::GetInstance();
    sf::Vector2f emitPos = GetEntity()->GetPos();
    sf::Vector2f targetPos;
    sf::Vector2f curPos;

    for (auto &enemy : gameInstance->GetGameBoard()->GetEnemies()) {
        curPos = enemy->GetPos();
        if (GetVectorMagnitude(curPos.x, curPos.y) > GetVectorMagnitude(targetPos.x, targetPos.y)) {
            targetPos = curPos;
        }
    }

    sf::Vector2f direction = (targetPos - emitPos);
    float directionMag = GetVectorMagnitude(direction.x, direction.y);

    ProjectileEntity* projectileEntity = new ProjectileEntity();
    ProjectileMovementComponent* projMoveComponent = static_cast<ProjectileMovementComponent*>(projectileEntity->AddComponent<ProjectileMovementComponent>());
    GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(projectileEntity->AddComponent<GameEngine::SpriteRenderComponent>());

    render->SetTexture(GameEngine::eTexture::Particles);
    render->SetZLevel(1);
    projMoveComponent->SetVector(sf::Vector2f(direction.x * 20 / directionMag, direction.y * 20 / directionMag));
    projMoveComponent->SetDuration(20.f);
    projectileEntity->SetPos(emitPos);
    projectileEntity->SetSize(sf::Vector2f(100.f, 100.f));
    projectileEntity->SetSource(static_cast<PlayerEntity*>(GetEntity()));
    projectileEntity->SetDamage(50.f);

    gameInstance->AddEntity(projectileEntity);
}
