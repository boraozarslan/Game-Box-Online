#include "ProjectileEmitterComponent.hpp"

using namespace Game;

ProjectileEmitterComponent::ProjectileEmitterComponent()
: m_toEmitTimer(0.f)
, m_projSpeed(50.f)
, m_reloadTime(0.3f)
{

}

ProjectileEmitterComponent::~ProjectileEmitterComponent()
{

}

void ProjectileEmitterComponent::Update()
{
    float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    m_toEmitTimer -= dt;

    if (m_toEmitTimer > 0.f || GameEngine::GameEngineMain::GetInstance()->IsGameOver()) {
        return;
    }

    sf::Vector2f proj_direction;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        proj_direction = sf::Vector2f(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        proj_direction = sf::Vector2f(1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        proj_direction = sf::Vector2f(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        proj_direction = sf::Vector2f(0.f, 1.f);
    } else {
        return;
    }

    m_toEmitTimer = RandomFloatRange(m_reloadTime * RELOAD_MIN_PERCENT, m_reloadTime);
    EmitProjectile(proj_direction);
}

void ProjectileEmitterComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}


void ProjectileEmitterComponent::OnRemoveFromWorld()
{
    Component::OnAddToWorld();
}


void ProjectileEmitterComponent::EmitProjectile(sf::Vector2f direction)
{
    sf::Vector2f emitPos = GetEntity()->GetPos();

    ProjectileEntity* projectileEntity = new ProjectileEntity();
    ProjectileMovementComponent* projMoveComponent = static_cast<ProjectileMovementComponent*>(projectileEntity->AddComponent<ProjectileMovementComponent>());
    GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(projectileEntity->AddComponent<GameEngine::SpriteRenderComponent>());
    GameEngine::AnimationComponent* animComponent = static_cast<GameEngine::AnimationComponent*>(projectileEntity->AddComponent<GameEngine::AnimationComponent>());

    direction.x *= m_projSpeed;
    direction.y *= m_projSpeed;

    projMoveComponent->SetVector(direction);

    render->SetTexture(GameEngine::eTexture::Particles);
    render->SetZLevel(1);

    projectileEntity->SetPos(emitPos);
    projectileEntity->SetSize(sf::Vector2f(16.f, 16.f));
    projectileEntity->SetSource(static_cast<PlayerEntity*>(GetEntity()));

    GameEngine::GameEngineMain::GetInstance()->AddEntity(projectileEntity);
}

void ProjectileEmitterComponent::setProjInfo(float projSpeed, float reloadTime) {
    m_projSpeed = projSpeed;
    m_reloadTime = reloadTime;
}
