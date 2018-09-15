#include "PlayerSoundComponent.hpp"

#include "GameEngine/GameEngineMain.hpp"
#include "GameEngine/EntitySystem/Components/SoundComponent.hpp"
#include "ResourcePath.hpp"

using namespace Game;

PlayerSoundComponent::PlayerSoundComponent()
{

}


PlayerSoundComponent::~PlayerSoundComponent()
{

}

void PlayerSoundComponent::OnAddToWorld()
{
	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
        std::string filepath = resourcePath();
		m_upSoundId   = soundComponent->LoadSoundFromFile(filepath + "thunder.wav");
		m_downSoundId = soundComponent->LoadSoundFromFile(filepath + "glassbreak.wav");
	}
}


void PlayerSoundComponent::Update()
{
	Component::Update();

	m_timeSinceLastUpSound += GameEngine::GameEngineMain::GetTimeDelta();
	m_timeSinceLastDownSound += GameEngine::GameEngineMain::GetTimeDelta();
}


void PlayerSoundComponent::RequestSound(bool upSound)
{
	static bool enablePlayerSounds = false;	
	if (!enablePlayerSounds)
		return;

	GameEngine::SoundManager::SoundId soundId = upSound ? m_upSoundId : m_downSoundId;
	float& lastPlayTimer =					    upSound ? m_timeSinceLastUpSound : m_timeSinceLastDownSound;
	

	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
		if (lastPlayTimer > 1.0f)
		{
			soundComponent->PlaySound(soundId);
			lastPlayTimer = 0.0f;
		}
	}
}
