#pragma once
#include "../../GameEngine/EntitySystem/Entity.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../GameComponents/ProjectileMovementComponent.hpp"
#include "PlayerEntity.hpp"

namespace Game
{

    class ProjectileEntity : public GameEngine::Entity
    {
    public:
        ProjectileEntity();
        ~ProjectileEntity();

        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;

        float GetDamage();
        void SetDamage(float damage);
        PlayerEntity* GetSource();
        void SetSource(PlayerEntity* source);
        void SetTexture(GameEngine::eTexture::type texture);
    protected:
        GameEngine::SpriteRenderComponent* m_renderComponent;
        ProjectileMovementComponent*   m_projectileMovementComponent;
        GameEngine::AnimationComponent* m_animComponent;
        float m_damage;
        PlayerEntity* m_source;
    };
}
