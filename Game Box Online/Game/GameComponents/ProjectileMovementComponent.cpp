#include "ProjectileMovementComponent.hpp"

#include "../../GameEngine/GameEngineMain.hpp"

#include "../../GameEngine/Util/TextureManager.hpp"
#include "../../GameEngine/Util/AnimationManager.hpp"

using namespace Game;

ProjectileMovementComponent::ProjectileMovementComponent(): current_vector(0.f, 0.f), duration_remaining(0.3f)
{

}

ProjectileMovementComponent::~ProjectileMovementComponent()
{

}

void ProjectileMovementComponent::OnAddToWorld()
{
    m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
}

void ProjectileMovementComponent::Update()
{
    Component::Update();

    float dt = GameEngine::GameEngineMain::GetTimeDelta();
    duration_remaining -= dt;

    if (duration_remaining <= 0.f) {
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());
    }

    GetEntity()->SetPos(GetEntity()->GetPos() + current_vector);
}

void ProjectileMovementComponent::SetVector(sf::Vector2f new_vector) {
    current_vector = new_vector;
}

void ProjectileMovementComponent::SetDuration(float duration) {
    duration_remaining = duration;
}
