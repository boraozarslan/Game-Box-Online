#pragma once
#include "../Component.hpp"
#include "./SpriteRenderComponent.hpp"
#include "./AnimationComponent.hpp"
#include "../../GameEngineMain.hpp"
#include "../../../Game/GameEntities/ProjectileEntity.hpp"
#include "../../../Game/GameEntities/PlayerEntity.hpp"

namespace GameEngine
{
    class DumbProjectileComponent: public Component
    {
    public:
        DumbProjectileComponent();
        virtual ~DumbProjectileComponent();

        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;

        virtual void Update() override;

        void SetTarget(Game::PlayerEntity* target);
    protected:
        static constexpr float RELOAD_MIN_PERCENT = 0.90f;

        void EmitProjectile();

        //Placeholder temp - should go to helpers or smth.
        float RandomFloatRange(float a, float b)
        {
            return ((b - a) * ((float)rand() / RAND_MAX)) + a;
        }

        float m_toEmitTimer;
        float m_projSpeed;
        float m_reloadTime;
    };
}
