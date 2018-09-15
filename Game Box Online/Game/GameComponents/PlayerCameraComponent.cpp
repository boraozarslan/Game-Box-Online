#include "PlayerCameraComponent.hpp"

#include "GameEngine/GameEngineMain.hpp"
#include "GameEngine/Util/CameraManager.hpp"

using namespace Game;

PlayerCameraComponent::PlayerCameraComponent()
{

}


PlayerCameraComponent::~PlayerCameraComponent()
{

}

void PlayerCameraComponent::OnAddToWorld()
{

}


void PlayerCameraComponent::Update()
{
	Component::Update();	
	
	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	GameEngine::CameraManager::GetInstance()->GetCameraView().setCenter(GetEntity()->GetPos());
}
