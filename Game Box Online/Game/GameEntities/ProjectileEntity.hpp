#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/ProjectileMovementComponent.hpp"

namespace Game
{

    class ProjectileEntity : public GameEngine::Entity
    {
    public:
        ProjectileEntity();
        ~ProjectileEntity();

        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;

    protected:
        GameEngine::SpriteRenderComponent* m_renderComponent;
        ProjectileMovementComponent*   m_projectileMovementComponent;
        GameEngine::AnimationComponent* m_animComponent;
        float damage;
    };
}
