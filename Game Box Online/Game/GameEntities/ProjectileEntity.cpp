#include "ProjectileEntity.hpp"

#include "../../GameEngine/EntitySystem/Components/CollidableComponent.hpp"
#include "../GameComponents/ProjectileEmitterComponent.hpp"

using namespace Game;

ProjectileEntity::ProjectileEntity(): m_damage(10.f), m_source(nullptr)
{
    m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
    AddComponent<GameEngine::CollidableComponent>();
    m_renderComponent->SetTexture(GameEngine::eTexture::Shuriken);
    m_renderComponent->SetZLevel(2);
    m_animComponent = static_cast<GameEngine::AnimationComponent*>(AddComponent<GameEngine::AnimationComponent>());
}


ProjectileEntity::~ProjectileEntity()
{

}


void ProjectileEntity::OnAddToWorld()
{
    GameEngine::Entity::OnAddToWorld();

    if (m_animComponent)
    {
        m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
    }
}


void ProjectileEntity::OnRemoveFromWorld()
{
    GameEngine::Entity::OnRemoveFromWorld();
}

float ProjectileEntity::GetDamage() {
    return m_damage;
}

void ProjectileEntity::SetDamage(float damage) {
    m_damage = damage;
}

void ProjectileEntity::SetSource(PlayerEntity* source) {
    m_source = source;
}

void ProjectileEntity::SetTexture(GameEngine::eTexture::type texture) {
    m_renderComponent->SetTexture(texture);
}

Game::PlayerEntity* ProjectileEntity::GetSource() {
    return m_source;
}
