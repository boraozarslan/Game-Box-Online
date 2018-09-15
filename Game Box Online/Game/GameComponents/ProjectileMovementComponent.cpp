#include "ProjectileMovementComponent.hpp"

#include "../../GameEngine/GameEngineMain.hpp"

#include "../../GameEngine/Util/TextureManager.hpp"
#include "../../GameEngine/Util/AnimationManager.hpp"

using namespace Game;

ProjectileMovementComponent::ProjectileMovementComponent(): current_vector(0.f, 0.f)
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

    if (GameEngine::GameEngineMain::GetInstance()->IsGameOver())
    {
        return;
    }

    GetEntity()->SetPos(GetEntity()->GetPos() + current_vector);
}

void ProjectileMovementComponent::setVector(sf::Vector2f new_vector) {
    current_vector = new_vector;
}
