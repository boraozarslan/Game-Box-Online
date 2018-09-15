#pragma once
#include "GameEngine/EntitySystem/Component.hpp"
#include "GameEngine/Util/SoundManager.hpp"

namespace Game
{
	class PlayerSoundComponent : public GameEngine::Component
	{
	public:
		PlayerSoundComponent();
		virtual ~PlayerSoundComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

		void RequestSound(bool upSound);

	private:		
		float m_timeSinceLastUpSound;
		float m_timeSinceLastDownSound;

		GameEngine::SoundManager::SoundId m_upSoundId;
		GameEngine::SoundManager::SoundId m_downSoundId;
	};
}


