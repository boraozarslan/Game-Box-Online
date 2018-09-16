#pragma once
#include "../../GameEngine/EntitySystem/Component.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/GameEngineMain.hpp"
#include "../GameEntities/ProjectileEntity.hpp"

namespace Game
{
    class ProjectileEmitterComponent: public GameEngine::Component
    {
    public:
        ProjectileEmitterComponent();
        virtual ~ProjectileEmitterComponent();

        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;

        virtual void Update() override;

        void setProjInfo(float projSpeed, float reloadTime);
    protected:
        static constexpr float RELOAD_MIN_PERCENT = 0.90f;

        void EmitProjectile(sf::Vector2f direction);

        //Placeholder temp - should go to helpers or smth.
        float RandomFloatRange(float a, float b)
        {
            return ((b - a) * ((float)rand() / RAND_MAX)) + a;
        }

        float m_toEmitTimer;
        float m_projSpeed;
        float m_reloadTime;
    private:
        bool m_keyReleased;
    };
}
