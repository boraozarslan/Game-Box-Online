#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../GameEngine/EntitySystem/Component.hpp"
#include "../../GameEngine/EntitySystem/Components/AnimationComponent.hpp"

namespace Game
{
    class ProjectileMovementComponent : public GameEngine::Component
    {
    public:
        ProjectileMovementComponent();
        ~ProjectileMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;

        // Sets the direction vector particle moves at
        void setVector(sf::Vector2f new_vector);

        GameEngine::AnimationComponent* m_animComponent;

    protected:
        sf::Vector2f current_vector;
        float duration_remaining;
    };
}


