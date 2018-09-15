#include "ProjectileEntity.hpp"

#include "../../GameEngine/EntitySystem/Components/CollidablePhysicsComponent.hpp"
#include "../GameComponents/ProjectileEmitterComponent.hpp"

using namespace Game;

ProjectileEntity::ProjectileEntity(): damage(10.f)
{
    m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
    AddComponent<GameEngine::CollidablePhysicsComponent>();
    m_renderComponent->SetTexture(GameEngine::eTexture::Player);
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
