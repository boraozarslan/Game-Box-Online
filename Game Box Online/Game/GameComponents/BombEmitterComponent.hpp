#pragma once
#include "../../GameEngine/EntitySystem/Component.hpp"
#include "../../GameEngine/EntitySystem/Components/SpriteRenderComponent.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"
#include "../../GameEngine/GameEngineMain.hpp"
#include "../GameEntities/ProjectileEntity.hpp"

namespace Game
{
    class BombEmitterComponent: public GameEngine::Component
    {
    public:
        BombEmitterComponent();
        virtual ~BombEmitterComponent();

        virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;

        virtual void Update() override;

        void FireBomb();

        float m_cooldownRemaining;
        float m_reloadTime;
    protected:
        // TODO(LEON): Put in helpers file
        float GetVectorMagnitude(float a, float b) {
            return sqrt(a * a + b * b);
        }
    };
}
